// udpcontrol.cpp
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

#include <QStringList>

#include "udpcontrol.h"

UdpControl::UdpControl(QObject *parent)
  : QObject(parent)
{
  udp_socket=new QUdpSocket(this);
  udp_socket->bind(UDPCONTROL_DEFAULT_PORT);
  connect(udp_socket,SIGNAL(readyRead()),this,SLOT(receivedData()));
}


UdpControl::~UdpControl()
{
  delete udp_socket;
}


void UdpControl::receivedData()
{
  int n;
  char data[1501];
  QHostAddress addr;
  QString accum;
  bool escaped=false;

  while((n=udp_socket->readDatagram(data,1500,&addr))>0) {
    for(int i=0;i<n;i++) {
      switch(data[i]) {
      case '!':
	if(escaped) {
	  accum+=data[i];
	  escaped=false;
	}
	else {
	  ProcessPacket(accum,(addr.toIPv4Address()>>24)==127);
	  accum="";
	}
	break;

      case '\\':
	if(escaped) {
	  accum+=data[i];
	  escaped=false;
	}
	else {
	  escaped=true;
	}
	break;

      default:
	accum+=data[i];
	break;
      }
    }
  }
}


void UdpControl::ProcessPacket(const QString &msg,bool is_local)
{
  QStringList f0=msg.split(" ");

  if(is_local) {
    if((f0[0]=="SN")&&(f0.size()>=2)) {     // Set Receiver Name
      f0.erase(f0.begin());
      emit changeReceiverName(f0.join(" "));
      return;
    }

    if((f0[0]=="SS")&&(f0.size()>=2)) {     // Set Stream URL
      f0.erase(f0.begin());
      emit changeStreamUrl(f0.join(" "));
      return;
    }

    if(f0[0]=="SV") {                       // Save Configuration
      emit saveConfiguration();
    }
  }
}
