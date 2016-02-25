// updatecontrol.cpp
//
// Firmware update control for GlassPlayerHost
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


#include <unistd.h>

#include <wh/whcgiapplication.h>

#include "upgradecontrol.h"

UpgradeControl::UpgradeControl(WHCgiPost *post)
  : WHCgiPage(post)
{
  QString ip_address;
  if(getenv("HTTP_HOST")!=NULL) {
    ip_address=getenv("HTTP_HOST");
  }
  setTitleText("GlassPlayer Restart");
  addScript("/refresh.js");
  addScript("/utils.js");
  setOnLoadEvent("RefreshPage('"+ip_address+"',"+
		 QString().sprintf("'%u'",UPGRADE_REFRESH_TIME)+");");
}


UpgradeControl::~UpgradeControl()
{
}


void UpgradeControl::render()
{
  QString pkgfile;

  if(!post()->isFile("PKGFILE")) {
    cgiapp->exit(400,"PKGFILE is not a file");
  }
  if(!post()->getValue("PKGFILE",&pkgfile)) {
    cgiapp->exit(400,"Missing PKGFILE");
  }
  post()->sendUpgradeCommand(pkgfile);

  //
  // Serve Refresh Page
  //
  printf("<b><td><br>&nbsp;&nbsp;&nbsp;GlassPlayer by RFA Labs</b>\n");
  printf("<hr>\n");
  printf("<table cellspacing=\"2\" cellpadding=\"2\" border=\"0\">\n");
  printf("<tr><td><strong>System Restarting</strong></td></tr>\n");
  printf("<tr><td id=\"REFRESH_TIMER\">&nbsp;</td></tr>\n");
  printf("</table>\n");
}
