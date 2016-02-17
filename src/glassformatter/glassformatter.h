// glassformatter.h
//
// glassformatter(1) Stat Processor for glassplayer(1)
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

#ifndef GLASSFORMATTER_H
#define GLASSFORMATTER_H

#include <QObject>
#include <QProcess>
#include <QTimer>

#include "statsstore.h"

#define GLASSFORMATTER_USAGE "[options]\n"

class MainObject : public QObject
{
 Q_OBJECT;
 public:
  MainObject(QObject *parent=0);

 private:
  StatsStore *format_store;
};


#endif  // GLASSFORMATTER_H
