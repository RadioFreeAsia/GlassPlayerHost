// homepage.cpp
//
//  Home page for GlassPlayerHost
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


#include "homepage.h"

HomePage::HomePage(WHCgiPost *post)
  : WHCgiPage(post)
{
  setTitleText("GlassPlayer by RFA Labs");
  setMenuText("Home");
  setMenuRef("/");
  addScript("/navbar.js");
  addScript("/utils.js");
}


HomePage::~HomePage()
{
}


void HomePage::render()
{
  printf("<table border=\"0\" cellPadding=\"4\" cellSpacing=\"2\" >\n");
  printf("<tbody>\n");

  //
  // Title Header
  //
  printf("<tr><td><strong>GlassPlayer by RFA Labs</td>\n");
  printf("<td>&nbsp;</td>\n");
  printf("</tr>\n");
  printf("<tr><td colspan=\"2\"><hr></td></tr>\n");

  //
  // Remote Control
  //
  printf("<tr bgColor=\"#a6a3a6\">\n");
  printf("<td align=\"center\" valign=\"middle\">\n");
  printf("<a href=\"javascript:callPlayerControl();\">Stream Setup</a>\n");
  printf("</td>\n");
  printf("<td bgcolor=\"#C6C3C6\">\n");
  printf("Configure Stream Receiver\n");
  printf("</td>\n"); 
  printf("</tr>\n");

  //
  // Configure IP Settings
  //
  printf("<tr bgColor=\"#a6a3a6\">\n");
  printf("<td align=\"center\" valign=\"middle\">\n");
  printf("<a href=\"javascript:callIpSettings();\">System</a>\n");
  printf("</td>\n");
  printf("<td bgcolor=\"#C6C3C6\">\n");
  printf("IP network address and settings,<br>Update Firmware\n");
  printf("</td>\n");
  printf("</tr>\n");

  printf("</tbody>\n");
  printf("</table>\n");
  printf("</center>\n");
}
