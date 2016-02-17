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


bool StatsStore::render(const QString &filename)
{
  FILE *f=NULL;

  if((f=fopen((filename+".temp").toUtf8(),"w"))==NULL) {
    return false;
  }

  fprintf(f,"<table cellpadding=\"0\" cellspacing=\"3\" border=\"0\" bgcolor=\"#FFFFFF\" width=\"900\">\n");
  for(std::map<QString,StatsValues *>::const_iterator it=store_values.begin();
      it!=store_values.end();it++) {
    it->second->render(f);
  }
  fprintf(f,"</table>\n");

  fclose(f);
  rename((filename+".temp").toUtf8(),filename.toUtf8());
  return true;
}
