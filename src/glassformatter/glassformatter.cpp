// glassformatter.cpp
//
// glassformatter(1) Stat Processor for glassplayer(1)
//
//   (C) Copyright 2016 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <QCoreApplication>

#include "glassformatter.h"
#include "paths.h"

bool global_reload=false;
void SigHandler(int signo)
{
  switch(signo) {
  case SIGHUP:
    global_reload=true;
    break;
  }
}


MainObject::MainObject(QObject *parent)
  : QObject(parent)
{
  //
  // Web Server
  //
  format_server=new WHHttpServer(this);
  connect(format_server,
	  SIGNAL(newSocketConnection(int,const QString &,const QString &)),
	  this,
	  SLOT(newSocketConnectionData(int,const QString &,const QString &)));
  connect(format_server,
	  SIGNAL(socketConnectionClosed(int,uint16_t,const QByteArray &)),
	  this,
	  SLOT(socketConnectionClosedData(int,uint16_t,const QByteArray &)));

  if(!format_server->listen(80)) {
    fprintf(stderr,"glassplayerhost: unable to bind port 80\n");
    exit(256);
  }
  format_server->loadUsers(GLASSPLAYERHOST_USER_FILE);
  format_server->addCgiSource("/",GLASSPLAYERHOST_CGI_DIR+"/glassplayerhost.cgi",
			    "GlassPlayer");
  format_server->addCgiSource("/glassplayerhost.cgi",
			    GLASSPLAYERHOST_CGI_DIR+"/glassplayerhost.cgi",
			    "GlassPlayer");

  format_server->addStaticSource("/glassplayer.js","application/javascript",
			       GLASSPLAYERHOST_SCRIPT_DIR+"/glassplayer.js",
			       "GlassPlayer");
  format_server->addStaticSource("/ipsystem.js","application/javascript",
			       GLASSPLAYERHOST_SCRIPT_DIR+"/ipsystem.js",
			       "GlassPlayer");
  format_server->addStaticSource("/navbar.js","application/javascript",
			       GLASSPLAYERHOST_SCRIPT_DIR+"/navbar.js",
			       "GlassPlayer");
  format_server->addStaticSource("/player.js","application/javascript",
			       GLASSPLAYERHOST_SCRIPT_DIR+"/player.js",
			       "GlassPlayer");
  format_server->addStaticSource("/refresh.js","application/javascript",
			       GLASSPLAYERHOST_SCRIPT_DIR+"/refresh.js",
			       "GlassPlayer");
  format_server->addStaticSource("/stats.js","application/javascript",
			       GLASSPLAYERHOST_SCRIPT_DIR+"/stats.js",
			       "GlassPlayer");
  format_server->addStaticSource("/utils.js","application/javascript",
			       GLASSPLAYERHOST_SCRIPT_DIR+"/utils.js",
			       "GlassPlayer");
  format_server->addStaticSource("/logo.png","image/png",
			       GLASSPLAYERHOST_SCRIPT_DIR+"/logo.png",
			       "GlassPlayer");
  format_server->addStaticSource("/stats.html","text/html",
			       GLASSPLAYERHOST_SCRIPT_DIR+"/stats.html",
			       "GlassPlayer");
  format_server->addStaticSource("/metadata.html","text/html",
			       GLASSPLAYERHOST_SCRIPT_DIR+"/metadata.html",
			       "GlassPlayer");
  format_server->addSocketSource("/","GlassPlayerMetadata","GlassPlayer");
  format_server->addSocketSource("/","GlassPlayerStats","GlassPlayer");

  //
  // Formatter
  //
  int flags=fcntl(0,F_GETFL);
  if(flags>=0) {
    flags|=O_NONBLOCK;
    fcntl(0,F_SETFL,flags);
  }
  format_notifier=new QSocketNotifier(0,QSocketNotifier::Read,this);
  connect(format_notifier,SIGNAL(activated(int)),this,SLOT(readyReadData(int)));

  //
  // Reload Timer
  //
  format_reload_timer=new QTimer(this);
  connect(format_reload_timer,SIGNAL(timeout()),this,SLOT(reloadData()));
  format_reload_timer->start(1000);

  //
  // Configure Signals
  //
  ::signal(SIGHUP,SigHandler);
}


void MainObject::newSocketConnectionData(int conn_id,const QString &uri,
					 const QString &proto)
{
  printf("Proto: %s\n",(const char *)proto.toUtf8());
  if(proto.toLower()=="glassplayermetadata") {
    NewMetadataConnection(conn_id);
    return;
  }
  if(proto.toLower()=="glassplayerstats") {
    NewStatsConnection(conn_id);
    return;
  }
  format_server->closeSocketConnection(conn_id,1008);
}


void MainObject::socketConnectionClosedData(int conn_id,uint16_t stat_code,
					    const QByteArray &body)
{
  for(unsigned i=0;i<format_metadata_ids.size();i++) {
    if(format_metadata_ids[i]==conn_id) {
      format_metadata_ids.erase(format_metadata_ids.begin()+i);
      return;
    }
  }
  for(unsigned i=0;i<format_stat_ids.size();i++) {
    if(format_stat_ids[i]==conn_id) {
      format_stat_ids.erase(format_stat_ids.begin()+i);
      return;
    }
  }
}


void MainObject::readyReadData(int fd)
{
  char data[1500];
  int n;

  while((n=read(0,data,1500))>0) {
    for(int i=0;i<n;i++) {
      switch(0xFF&data[i]) {
      case 10:
	ProcessLine(format_accum);
	format_accum="";
	break;
	
      default:
	format_accum+=0xFF&data[i];
	break;
      }
    }
  }
}


void MainObject::reloadData()
{
  if(global_reload) {
    format_server->loadUsers(GLASSPLAYERHOST_USER_FILE);
    global_reload=false;
  }
}


void MainObject::NewMetadataConnection(int conn_id)
{
  format_metadata_ids.push_back(conn_id);
  if(!format_metadata["Metadata|StreamTitle"].isEmpty()) {
    SendMetadata(conn_id,"StreamTitle","Stream Title",
		 "<strong><big>"+format_metadata["Metadata|StreamTitle"]+
		 "</big></strong>");
  }
  if(!format_metadata["Metadata|StreamUrl"].isEmpty()) {
    SendMetadata(conn_id,"StreamUrl","Stream URL",
		 "<img width=\"100\" height=\"100\" src=\""+
		 format_metadata["Metadata|StreamUrl"]+"\">");
  }
  if(!format_metadata["Metadata|Name"].isEmpty()) {
    SendMetadata(conn_id,"Name","<strong>Name:</strong> ",
		 format_metadata["Metadata|Name"]);
  }
  if(!format_metadata["Metadata|Description"].isEmpty()) {
    SendMetadata(conn_id,"Description","<strong>Description:</strong> ",
		 format_metadata["Metadata|Description"]);
  }
  if(!format_metadata["Metadata|ChannelUrl"].isEmpty()) {
    SendMetadata(conn_id,"ChannelUrl","<strong>Channel URL:</strong> ",
		 format_metadata["Metadata|ChannelUrl"]);
  }
  if(!format_metadata["Metadata|Genre"].isEmpty()) {
    SendMetadata(conn_id,"Genre","<strong>Genre:</strong> ",
		 format_metadata["Metadata|Genre"]);
  }
}


void MainObject::NewStatsConnection(int conn_id)
{
  QStringList f0;
  QString category;
  QString label;

  format_stat_ids.push_back(conn_id);
  for(std::map<QString,QString>::const_iterator it=format_stats.begin();
      it!=format_stats.end();it++) {
    f0=it->first.split("|",QString::KeepEmptyParts);
    category=f0[0];
    f0.erase(f0.begin());
    label=f0.join("|");
    printf("SendStat(%s,%s,%s,%s)\n",
	   (const char *)it->first.toUtf8(),
	   (const char *)category.toUtf8(),
	   (const char *)label.toUtf8(),
	   (const char *)it->second.toUtf8());
    SendStat(conn_id,it->first,category,label,it->second);
  }

  for(std::map<QString,QString>::const_iterator it=format_metadata.begin();
      it!=format_metadata.end();it++) {
    f0=it->first.split("|",QString::KeepEmptyParts);
    category=f0[0];
    f0.erase(f0.begin());
    label=f0.join("|");
    SendStat(conn_id,it->first,category,label,it->second);
  }
}


void MainObject::SendMetadata(int conn_id,const QString &name,
			      const QString &label,const QString &value)
{
  QStringList tags;
  QStringList values;

  tags.push_back("name");
  values.push_back(name);
  tags.push_back("label");
  values.push_back(label);
  tags.push_back("value");
  values.push_back(value);
  QString msg=MakeJson(tags,values);

  format_server->sendSocketMessage(conn_id,msg);
}


void MainObject::SendStat(int conn_id,const QString &name,
			  const QString &category,const QString &label,
			  const QString &value)
{
  QStringList tags;
  QStringList values;

  tags.push_back("name");
  values.push_back(name);
  tags.push_back("category");
  values.push_back(category);
  tags.push_back("label");
  values.push_back(label);
  tags.push_back("value");
  values.push_back(value);
  QString msg=MakeJson(tags,values);

  format_server->sendSocketMessage(conn_id,msg);
}


void MainObject::ProcessLine(const QString &str)
{
  QStringList f0=str.split(": ",QString::KeepEmptyParts);
  QString hdr=f0[0];
  QStringList f1=f0[0].split("|",QString::KeepEmptyParts);
  QString category=f1[0];
  f0.erase(f0.begin());
  QString value=f0.join(": ");
  f1.erase(f1.begin());
  QString label=f1.join("|");

  if(category=="Metadata") {
    if(label=="StreamTitle") {
      for(unsigned i=0;i<format_metadata_ids.size();i++) {
	SendMetadata(format_metadata_ids[i],"StreamTitle","Stream Title",
		     "<strong><big>"+value+"</big></strong>");
      }
    }
    if(label=="StreamUrl") {
      for(unsigned i=0;i<format_metadata_ids.size();i++) {
	SendMetadata(format_metadata_ids[i],"StreamUrl","Stream URL",
		     "<img width=\"100\" height=\"100\" src=\""+value+"\">");
      }
    }
    format_metadata[hdr]=value;

    for(unsigned i=0;i<format_stat_ids.size();i++) {
      SendStat(format_stat_ids[i],hdr,category,label,value);
    }
  }
  else {
    if(format_stats[hdr]!=value) {
      for(unsigned i=0;i<format_stat_ids.size();i++) {
	SendStat(format_stat_ids[i],hdr,category,label,value);
      }
    }
    format_stats[hdr]=value;
  }
}


QString MainObject::MakeJson(QStringList tags,QStringList values)
{
  QString ret="{";

  for(int i=0;i<tags.size();i++) {
    ret+="\""+tags[i]+"\": \""+values[i].replace("\"","\\\"")+"\",";
  }
  ret=ret.left(ret.length()-1)+"}";

  return ret;
}


int main(int argc,char *argv[])
{
  QCoreApplication a(argc,argv);
  new MainObject();
  return a.exec();
}
