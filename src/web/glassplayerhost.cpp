// glassplayerhost.cpp
//
// GlassPlayerHost CGI application.
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

#include <stdio.h>
#include <stdlib.h>

#include <QCoreApplication>

#include <wh/whcgipage.h>

#include "cgicommands.h"
#include "homepage.h"
#include "playercontrol.h"
#include "playerpage.h"
#include "systemcontrol.h"
#include "systempage.h"
#include "glassplayerhost.h"
#include "upgradecontrol.h"

MainObject::MainObject(QObject *parent)
  : WHCgiApplication(parent)
{
  addPage(0,new HomePage(post()));
  addPage(CGI_COMMAND_SERVE_GLASSPLAYER_CONFIG,new PlayerPage(post()));
  addPage(CGI_COMMAND_COMMIT_GLASSPLAYER_CONFIG,new PlayerControl(post()));
  addPage(CGI_COMMAND_SERVE_IPSETTINGS,new SystemPage(post()));
  addPage(CGI_COMMAND_COMMIT_IPSETTINGS,new SystemControl(post()));
  addPage(CGI_COMMAND_UPLOAD_FIRMWARE,new UpgradeControl(post()));
}


int main(int argc,char *argv[])
{
  QCoreApplication a(argc,argv);
  new MainObject();
  return a.exec();
}
