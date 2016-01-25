// playercontrol.cpp
//
// Player settings control for GlassPlayerHost
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

#include <wh/whcgiapplication.h>

#include "playercontrol.h"

PlayerControl::PlayerControl(WHCgiPost *post)
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
		 QString().sprintf("'%u'",PLAYERCONTROL_REFRESH_TIME)+");");
}


PlayerControl::~PlayerControl()
{
}


void PlayerControl::render()
{
  QUrl stream_url;

  if(!post()->getValue("STREAM_URL",&stream_url)) {
    cgiapp->exit(400,"Missing STREAM_URL");
  }
  if(!stream_url.isValid()) {
    cgiapp->exit(400,"Invalid STREAM_URL");
  }
  post()->sendUdpPacket(("SS "+stream_url.toString()+"!").toUtf8(),6060);
  post()->sendUdpPacket("SV!",6060);
  post()->sendRestartCommand("glassplayerhost");

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
