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

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <QCoreApplication>

#include "glassformatter.h"
#include "paths.h"

MainObject::MainObject(QObject *parent)
  : QObject(parent)
{
  char line[1024];
  QString str;

  format_store=new StatsStore();

  while(fgets(line,1024,stdin)!=NULL) {
    str=QString(line).trimmed();
    if(str.isEmpty()) {
      if(!format_store->renderStats(GLASSPLAYERHOST_SCRIPT_DIR+"/stats.html")) {
	fprintf(stderr,"glassformatter: unable to write stats file\n");
      }
      if(!format_store->
	 renderMetadata(GLASSPLAYERHOST_SCRIPT_DIR+"/metadata.html")) {
	fprintf(stderr,"glassformatter: unable to write metadata file\n");
      }
    }
    else {
      format_store->update(str);
    }
  }

  unlink("/var/www/html/stats/stats.html");
  unlink("/var/www/html/stats/metadata.html");
  exit(0);
}


int main(int argc,char *argv[])
{
  QCoreApplication a(argc,argv);
  new MainObject();
  return a.exec();
}
