// playerpage.cpp
//
// Player control page for GlassPlayerHost
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

#include "cgicommands.h"
#include "config.h"
#include "playerpage.h"

PlayerPage::PlayerPage(WHCgiPost *post)
  : WHCgiPage(post)
{
  setTitleText("GlassPlayer Configuration (IP Settings)");
  setMenuText("Player");
  setMenuRef("javascript:callPlayerControl();");
  addScript("/glassplayer.js");
  addScript("/navbar.js");
  addScript("/utils.js");
}


PlayerPage::~PlayerPage()
{
}


void PlayerPage::render()
{
  Config *config=new Config();
  config->load();

  printf("<table cellspacing=\"2\" cellpadding=\"2\" border=\"0\"><tbody>\n");
  printf("<tr class='tab-head'><td colspan=\"2\">Stream Receiver Setup</td></tr>\n");

  //
  // Stream URL
  //
  printf("<tr><td>Stream URL:</td><td>\n");
  printf("<input id=\"STREAM_URL\" name=\"STREAM_URL\" size=\"60\" maxlength=\"512\" value=\"%s\">\n",(const char *)config->streamUrl().toUtf8());
  printf("<br></td>\n");
  printf("</tr>\n");

  //
  // Apply Button
  //
  printf("<tr><td colspan=\"2\">&nbsp;</td></tr>\n");
  printf("<tr><td colspan=\"2\"><center><input type=\"button\" onclick=\"applyGlassPlayerSettings();\" value=\"Apply\"></center></td></tr>\n");

  printf("</table>\n");
}
