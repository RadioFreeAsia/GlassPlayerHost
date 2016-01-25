// systemcontrol.cpp
//
// System control for GlassPlayerHost
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

#include <wh/whcgiapplication.h>

#include "systemcontrol.h"

SystemControl::SystemControl(WHCgiPost *post)
  : WHCgiPage(post)
{
  QString ip_address;
  if(getenv("HTTP_HOST")!=NULL) {
    ip_address=getenv("HTTP_HOST");
  }
  setTitleText("GlassPlayer Restart");
  addScript("/refresh.js");
  addScript("/utils.js");
  setOnLoadEvent("RefreshPage('"+ip_address+"',"+SYSTEM_REFRESH_TIME+");");
}


SystemControl::~SystemControl()
{
}


void SystemControl::render()
{
  QString ip_address;
  QString ip_netmask;
  QString ip_gateway;
  QString ip_dns1;
  QString ip_dns2;
  QString timezone;
  QString ntp1;
  QString ntp2;
  QString password;

  //
  // Process IP Parameters
  //
  if(!post()->getValue("IP_ADDRESS",&ip_address)) {
    cgiapp->exit(400,"Missing IP_ADDRESS");
  }
  if(!post()->getValue("IP_NETMASK",&ip_netmask)) {
    cgiapp->exit(400,"Missing IP_NETMASK");
  }
  if(!post()->getValue("IP_GATEWAY",&ip_gateway)) {
    cgiapp->exit(400,"Missing IP_GATEWAY");
  }
  post()->getValue("IP_DNS1",&ip_dns1);
  post()->getValue("IP_DNS2",&ip_dns2);
  if(ip_dns1.isEmpty()&&ip_dns2.isEmpty()) {
    cgiapp->exit(400,"Missing DNS server values");
  }

  //
  // Process NTP Parameters
  //
  if(!post()->getValue("TIME_ZONE",&timezone)) {
    cgiapp->exit(400,"Missing TIME_ZONE");
  }
  post()->getValue("NTP_ADDRESS0",&ntp1);
  post()->getValue("NTP_ADDRESS1",&ntp2);
  if(ntp1.isEmpty()&&ntp2.isEmpty()) {
    cgiapp->exit(400,"Missing NTP server values");
  }

  //
  // Process Password Parameters
  //
  if(!post()->getValue("PASSWORD",&password)) {
    cgiapp->exit(400,"Missing PASSWORD");
  }

  //
  // Apply Settings
  //
  post()->sendIpCommand(1,QHostAddress(ip_address),QHostAddress(ip_netmask),
			QHostAddress(ip_gateway),QHostAddress(ip_dns1),
			QHostAddress(ip_dns2));
  post()->sendNtpCommand(timezone,ntp1,ntp2);
  if(password!="********") {
    post()->sendAddUserCommand("/etc/httpd/conf.d/glassplayerhost.htpasswd","user",
			       password);
  }
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
