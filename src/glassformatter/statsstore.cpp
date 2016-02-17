// statsstore.cpp
//
// Statistics data store.
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

#include <QStringList>

#include "config.h"
#include "statsstore.h"

StatsStore::StatsStore()
{
}


void StatsStore::update(const QString &str)
{
  QStringList f0=str.trimmed().split(": ",QString::KeepEmptyParts);
  if(f0.size()>=2) {
    QStringList f1=f0[0].trimmed().split("|",QString::KeepEmptyParts);
    if(f1.size()>=2) {
      QString category=f1[0].trimmed();
      f1.erase(f1.begin());
      QString param=f1.join("|").trimmed();
      f0.erase(f0.begin());
      QString value=f0.join(": ").trimmed();
      if(store_values[category]==NULL) {
	store_values[category]=new StatsValues(category);
      }
      store_values[category]->update(param,value);
    }
  }
}


bool StatsStore::renderStats(const QString &filename)
{
  FILE *f=NULL;

  if((f=fopen((filename+".temp").toUtf8(),"w"))==NULL) {
    return false;
  }

  fprintf(f,"<table cellpadding=\"0\" cellspacing=\"3\" border=\"0\" bgcolor=\"#FFFFFF\" width=\"%d\">\n",GLASSPLAYERHOST_WEB_WIDTH);
  for(std::map<QString,StatsValues *>::const_iterator it=store_values.begin();
      it!=store_values.end();it++) {
    it->second->render(f);
  }
  fprintf(f,"</table>\n");

  fclose(f);
  rename((filename+".temp").toUtf8(),filename.toUtf8());
  return true;
}


bool StatsStore::renderMetadata(const QString &filename)
{
  FILE *f=NULL;
  StatsValues *meta_values=store_values["Metadata"];
  QStringList params;
  QStringList values;

  if(meta_values==NULL) {
    return false;
  }
  if((f=fopen((filename+".temp").toUtf8(),"w"))==NULL) {
    return false;
  }

  if(!meta_values->value("Name").isEmpty()) {
    params.push_back("Name");
    values.push_back(meta_values->value("Name"));
  }
  if(!meta_values->value("Description").isEmpty()) {
    params.push_back("Description");
    values.push_back(meta_values->value("Description"));
  }
  if(!meta_values->value("ChannelUrl").isEmpty()) {
    params.push_back("Channel URL");
    values.push_back(meta_values->value("ChannelUrl"));
  }
  if(!meta_values->value("Genre").isEmpty()) {
    params.push_back("Genre");
    values.push_back(meta_values->value("Genre"));
  }

  fprintf(f,"<table cellpadding=\"0\" cellspacing=\"5\" border=\"0\" width=\"%d\" bgcolor=\"#FFFFFF\">\n",GLASSPLAYERHOST_WEB_WIDTH);
  if(meta_values->value("StreamTitle").isEmpty()) {
    fprintf(f,"<tr><td colspan=\"2\">&nbsp;</td>\n");
  }
  else {
    fprintf(f,"<tr><td colspan=\"2\"><big><strong>%s</strong></big></td>\n",
	    (const char *)meta_values->value("StreamTitle").toUtf8());
  }
  if(meta_values->value("StreamUrl").isEmpty()) {
    fprintf(f,"<td rowspan=\"%d\" width=\"100\">&nbsp;</td></tr>\n",params.size()+1);
  }
  else {
    fprintf(f,"<td width=\"100\" rowspan=\"%d\"><img src=\"%s\" height=\"100\" width=\"100\"></td></tr>\n",
	    params.size()+1,
	    (const char *)meta_values->value("StreamUrl").toUtf8());
  }
  for(int i=0;i<params.size();i++) {
    fprintf(f,
	  "<tr valign=\"top\"><td align=\"right\"><strong>%s:</strong></td>\n",
	    (const char *)params[i].toUtf8());
    fprintf(f,"<td align=\"left\">%s</td></tr>\n",
	    (const char *)values[i].toUtf8());
  }
  fprintf(f,"</table>\n");

  fclose(f);
  rename((filename+".temp").toUtf8(),filename.toUtf8());
  return true;
}
