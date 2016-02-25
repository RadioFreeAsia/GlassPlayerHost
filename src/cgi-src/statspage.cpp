// statspage.cpp
//
// Stats control page for GlassPlayerHost
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

#include <wh/whnetwork.h>
#include <wh/whprofile.h>

#include "cgicommands.h"
#include "config.h"
#include "statspage.h"

StatsPage::StatsPage(WHCgiPost *post)
  : WHCgiPage(post)
{
  setTitleText("GlassPlayer Stream Statistics");
  setMenuText("Stats");
  setMenuRef("javascript:callStats();");
  addScript("/stats.js");
  addScript("/navbar.js");
  addScript("/utils.js");
  setOnLoadEvent("StartStats();");
}


StatsPage::~StatsPage()
{
}


void StatsPage::render()
{
  printf("<table cellspacing=\"2\" cellpadding=\"2\" border=\"0\" width=\"%d\"><tbody>\n",GLASSPLAYERHOST_WEB_WIDTH);
  printf("<tr class='tab-head'><td>Stream Statistics</td></tr>\n");

  printf("<tr><td name=\"STATS\" id=\"STATS\">&nbsp;</td></tr>\n");

  printf("</table>\n");
}
