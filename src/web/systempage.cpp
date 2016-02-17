// systempage.cpp
//
// System control page for GlassPlayerHost
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
#include "systempage.h"

SystemPage::SystemPage(WHCgiPost *post)
  : WHCgiPage(post)
{
  setTitleText("GlassPlayer Configuration (IP Settings)");
  setMenuText("System");
  setMenuRef("javascript:callIpSettings();");
  addScript("/navbar.js");
  addScript("/ipsystem.js");
  addScript("/utils.js");
}


SystemPage::~SystemPage()
{
}


void SystemPage::render()
{
  printf("<table cellspacing=\"2\" cellpadding=\"2\" border=\"0\" width=\"%d\">\n",GLASSPLAYERHOST_WEB_WIDTH);

  //
  // IP Settings
  //
  printf("<tr class='tab-head'><td colspan=\"3\">IP Settings</td></tr>\n");

  //
  // IP Address
  //
  printf("<tr><td>Network address:</td><td>\n");
  printf("<input id=\"IP_ADDRESS\" name=\"IP_ADDRESS\" size=\"18\" maxlength=\"15\" value=\"%s\">\n",(const char *)post()->ipAddress(0).toString().toAscii());
  printf("</td>\n");
  printf("<td id=\"IP_ADDRESS_ERR\">&nbsp;</td>\n");
  printf("</tr>\n");

  //
  // Netmask
  //
  printf("<tr><td>Netmask:</td><td>\n");
  printf("<INPUT id=\"IP_NETMASK\" name=\"IP_NETMASK\" size=\"18\" maxlength=\"15\" value=\"%s\">\n",(const char *)post()->ipNetmask(0).toString().toAscii());
  printf("<td id=\"IP_NETMASK_ERR\">&nbsp;</td>\n");
  printf("</td></tr>\n");

  //
  // Gateway
  //
  printf("<tr><td>Gateway:</td><td>\n");
  printf("<input id=\"IP_GATEWAY\" name=\"IP_GATEWAY\" size=\"18\" maxlength=\"15\" value=\"%s\">\n",(const char *)post()->ipGateway().toString().toAscii());
  printf("<td id=\"IP_GATEWAY_ERR\">&nbsp;</td>\n");
  printf("</td></tr>\n");
  printf("<tr><td colspan=\"3\">&nbsp;</td></tr>\n");

  //
  // DNS1
  //
  printf("<tr><td>DNS 1:</td><td>\n");
  printf("<input id=\"IP_DNS1\" name=\"IP_DNS1\" size=\"18\" maxlength=\"15\" value=\"%s\">\n",(const char *)post()->dnsAddress(0).toString().toAscii());
  printf("<td id=\"IP_DNS1_ERR\">&nbsp;</td>\n");
  printf("</td></tr>\n");

  //
  // DNS2
  //
  printf("<tr><td>DNS 2:</td><td>\n");
  printf("<input id=\"IP_DNS2\" name=\"IP_DNS2\" size=\"18\" maxlength=\"15\" value=\"%s\">\n",(const char *)post()->dnsAddress(1).toString().toAscii());
  printf("<td id=\"IP_DNS2_ERR\">&nbsp;</td>\n");
  printf("</td></tr>\n");
  printf("<tr><td colspan=\"3\">&nbsp;</td></tr>\n");


  //
  // Time Settings
  //
  printf("<tr class='tab-head'><td colspan=\"3\">Time Settings</td></tr>\n");

  //
  // Time Zone
  //
  printf("<tr><td>Time zone:</td>\n");
  printf("<td colspan=\"2\"><select id=\"TIME_ZONE\" name=\"TIME_ZONE\">\n");
  QStringList zones=post()->timezoneList();
  QString current_timezone=post()->currentTimezone();

  for(int i=0;i<zones.size();i++) {
    printf("<option value=%s",(const char *)zones[i].toAscii());
    if(current_timezone==zones[i]) {
	printf(" selected");
      }
    printf(">%s</option>\n",(const char *)zones[i].toAscii());
  }
  printf("</select></td>\n");
  printf("</tr>\n");

  for(int i=0;i<WEBHOST_MAX_NTP_SERVERS;i++) {
    printf("<tr><td>NTP server %d:</td>\n",i+1);
    printf("<td><input id=\"NTP_ADDRESS%d\" name=\"NTP_ADDRESS%d\" size=18 maxlength=256 value=\"%s\"></td>\n",i,i,
	   (const char *)post()->ntpHostname(i).toUtf8());
    printf("<td id=\"NTP_ADDRESS%d_ERR\">&nbsp;</td>\n",i);
    printf("</tr>\n");
  }
  printf("<tr><td colspan=\"3\">&nbsp;</td></tr>\n");

  //
  // Password
  //
  printf("<tr class='tab-head'><td colspan=\"3\">Connection Password</td></tr>\n");
  printf("<tr><td>New password:</td><td colspan=\"2\"><input id=\"PASSWORD1\" type=\"password\" size=\"16\" maxlength=\"8\" value=\"********\">(5-8 characters: letters and numbers)</td></tr>\n");
  printf("<tr><td>Retype new password:</td><td colspan=\"2\"><input id=\"PASSWORD2\" type=\"password\" size=\"16\" maxlength=\"8\" value=\"********\">(verify)</td></tr>\n");
  printf("<tr><td align=\"center\" id=\"PASSWORD_ERR\" colspan=\"3\">&nbsp;</td></tr>\n");

  //
  // Apply Button
  //
  printf("<tr><td align=\"center\" colspan=\"3\">WARNING: System will restart after applying new settings.</td></tr>\n");
  printf("<tr><td colspan=\"3\"><CENTER><INPUT type=\"button\" onclick=\"validateIpSettings()\" value=\"Apply\"></CENTER></td></tr>\n");

  //
  // Firmware Version
  //
  //  printf("<form action=\"/cgi-bin/glassplayerhost.cgi\" method=\"post\" enctype=\"multipart/form-data\">\n");
  printf("<tr><td colspan=\"3\">&#160;<form action=\"/cgi-bin/glassplayerhost.cgi\" method=\"post\" enctype=\"multipart/form-data\"></td></tr>\n");
  printf("<tr class='tab-head'><td colspan=\"3\">Running Firmware Version: %s</td></tr>\n",VERSION);
  printf("<tr><td align=\"left\">\n");
  printf("<input type=\"hidden\" name=\"COMMAND\" value=\"%u\">\n",
	 CGI_COMMAND_UPLOAD_FIRMWARE);

//  printf("<tr><td align=\"left\">Install updated firmware package:</td>\n");
  printf("Install updated firmware package:</td>\n");
  printf("<td><input name=\"PKGFILE\" type=\"file\" id=\"PKGFILE\" /></td>\n");
  printf("<td><input type=\"submit\" value=\"Install\"></form></td></tr>\n");
  printf("<tr><td colspan=\"3\">&#160;</td></tr>\n");
  printf("</table>\n");
  //  printf("</tbody></table>\n");
}
