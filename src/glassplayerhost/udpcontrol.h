// udpcontrol.h
//
// UDP Control Class for GlassPlayerHost
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

#ifndef UDPCONTROL_H
#define UDPCONTROL_H

#include <QObject>
#include <QString>
#include <QUdpSocket>

#define UDPCONTROL_DEFAULT_PORT 6060

class UdpControl : public QObject
{
  Q_OBJECT;
 public:
  UdpControl(QObject *parent=0);
  ~UdpControl();

 signals:
  void changeReceiverName(const QString &str);
  void changeStreamUrl(const QString &url);
  void saveConfiguration();

 private slots:
  void receivedData();

 private:
  void ProcessPacket(const QString &msg,bool is_local);
  QUdpSocket *udp_socket;
};


#endif  // UDPCONTROL_H
