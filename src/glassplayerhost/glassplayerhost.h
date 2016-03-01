// glassplayerhost.h
//
// glassplayerhost(1) Launcher for glassplayer(1)
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

#ifndef GLASSPLAYERHOST_H
#define GLASSPLAYERHOST_H

#include <QObject>
#include <QProcess>
#include <QTimer>

#include "config.h"
#include "udpcontrol.h"

#define GLASSPLAYERHOST_RESTART_INTERVAL 1000
#define GLASSPLAYERHOST_WATCHDOG_INTERVAL 1000
#define GLASSPLAYERHOST_USAGE "[options]\n"

class MainObject : public QObject
{
 Q_OBJECT;
 public:
  MainObject(QObject *parent=0);

 private slots:
  void changeStreamUrlData(const QString &url);
  void changeReceiverNameData(const QString &str);
  void saveConfigurationData();
  void playerFinishedData(int exit_code,QProcess::ExitStatus status);
  void playerErrorData(QProcess::ProcessError err);
  void restartData();
  void exitData();
  void watchdogData();

 private:
  UdpControl *host_udp_control;
  QProcess *host_player_process;
  QProcess *host_formatter_process;
  QTimer *host_restart_timer;
  QTimer *host_exit_timer;
  QTimer *host_watchdog_timer;
  Config *host_config;
};


#endif  // GLASSPLAYERHOST_H
