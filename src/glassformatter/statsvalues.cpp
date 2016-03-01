// statsvalues.cpp
//
// Container class for a statistics category.
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

#include "statsvalues.h"

StatsValues::StatsValues(const QString &category)
{
  values_category=category;
}


QString StatsValues::value(const QString &param)
{
  return values_values[param];
}


bool StatsValues::update(const QString &param,const QString &value)
{
  bool ret=values_values[param]!=value;

  values_values[param]=value;
  return ret;
}


void StatsValues::render(FILE *f)
{
  fprintf(f,"<tr><td colspan=\"2\"><big><big><strong>%s</strong></big></big></td></tr>\n",(const char *)values_category.toUtf8());
  for(std::map<QString,QString>::const_iterator it=values_values.begin();
      it!=values_values.end();it++) {
    fprintf(f,"<tr><td valign=\"top\" align=\"right\"><strong>%s:</strong></td><td>%s</td></tr>\n",
	    (const char *)it->first.toUtf8(),
	    (const char *)it->second.toUtf8());
  }
  fprintf(f,"<tr><td colspan=\"2\"><hr></td></tr>\n");
}
