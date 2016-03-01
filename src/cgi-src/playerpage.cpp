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

#include <wh/whnetwork.h>
#include <wh/whprofile.h>

#include "cgicommands.h"
#include "config.h"
#include "playerpage.h"

PlayerPage::PlayerPage(WHCgiPost *post)
  : WHCgiPage(post)
{
  setTitleText("GlassPlayer Stream Settings");
  setMenuText("Player");
  setMenuRef("javascript:callPlayerControl();");
  addScript("/glassplayer.js");
  addScript("/navbar.js");
  addScript("/player.js");
  addScript("/utils.js");
  setOnLoadEvent("StartMetadata();");
}


PlayerPage::~PlayerPage()
{
}


void PlayerPage::render()
{
  QString iface;
  Config *config=new Config();
  config->load();

  WHProfile *p=new WHProfile();
  p->setSource(WEBHOST_CONF_FILE);
  iface=p->stringValue("Webhost","NetworkInterface1","eth0");
  delete p;

  printf("<table cellspacing=\"2\" cellpadding=\"2\" border=\"0\" width=\"%d\"><tbody>\n",GLASSPLAYERHOST_WEB_WIDTH);

  //
  // Metadata
  //
  printf("<tr class='tab-head'><td colspan=\"2\">Now Playing</td></tr>\n");
  printf("<tr><td colspan=\"2\" name=\"METADATA\" id=\"METADATA\">\n");
  printf("<table cellspacing=\"2\" cellpadding=\"2\" border=\"0\" width=\"%d\" bgcolor=\"#FFFFFF\">\n",GLASSPLAYERHOST_WEB_WIDTH);
  printf("<tr><td colspan=\"2\" id=\"StreamTitle\">&nbsp;</td></tr>\n");
  printf("<tr>\n");
  printf("<td align=\"right\" valign=\"top\" width=\"100\" id=\"StreamUrl\">&nbsp;</td>\n");
  printf("<td align=\"left\" valign=\"top\">\n");
  printf("<table cellspacing=\"2\" cellpadding=\"2\" border=\"0\" id=\"ChannelFields\">\n");
  printf("</table>\n");
  printf("</td>\n");
  printf("</tr>\n");

  printf("</table>\n");
  printf("</td></tr>\n");
  printf("<tr><td colspan=\"2\">&nbsp;</td></tr>\n");

  //
  // Receiver Parameters
  //
  printf("<tr class='tab-head'><td colspan=\"2\">Receiver Parameters</td></tr>\n");

  //
  // Receiver Name
  //
  printf("<tr><td>Name:</td><td>\n");
  printf("<input id=\"RECEIVER_NAME\" name=\"RECEIVER_NAME\" size=\"30\" maxlength=\"512\" value=\"%s\">\n",(const char *)config->systemName().toUtf8());
  printf("<br></td>\n");
  printf("</tr>\n");

  //
  // Receiver MAC Address
  //
  printf("<tr><td>MAC Address:</td><td>\n");
  printf("<strong>%s</strong>\n",(const char *)WHMacAddressText(WHInterfaceMacAddress(iface)).toUtf8());
  printf("<br></td>\n");
  printf("</tr>\n");

  //
  // Spacer
  //
  printf("<tr><td colspan=\"2\">&nbsp;</td></tr>\n");

  printf("<tr class='tab-head'><td colspan=\"2\">Stream Parameters</td></tr>\n");

  //
  // Stream URL
  //
  printf("<tr><td>Source URL:</td><td>\n");
  printf("<input id=\"STREAM_URL\" name=\"STREAM_URL\" size=\"80\" maxlength=\"512\" value=\"%s\">\n",(const char *)config->streamUrl().toUtf8());
  printf("<br></td>\n");
  printf("</tr>\n");

  //
  // Apply Button
  //
  printf("<tr><td colspan=\"2\">&nbsp;</td></tr>\n");
  printf("<tr><td colspan=\"2\"><center><input type=\"button\" onclick=\"applyGlassPlayerSettings();\" value=\"Apply\"></center></td></tr>\n");

  printf("</table>\n");
}
