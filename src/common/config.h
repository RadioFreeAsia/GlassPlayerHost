// config.h
//
// Class for reading GlassPlayerHost configuration.
//
// (C) Copyright 2015 Fred Gleason <fredg@paravelsystems.com>
//     All Rights Reserved.
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

#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

#define GLASSPLAYERHOST_DEFAULT_CONF_FILE "/etc/glassplayerhost.conf"

class Config
{
 public:
  Config();
  QString systemName() const;
  void setSystemName(const QString &str);
  QString alsaDevice() const;
  void setAlsaDevice(const QString &str);
  QString audioDevice() const;
  void setAudioDevice(const QString &str);
  QString streamUrl() const;
  void setStreamUrl(const QString &str);
  void load(const QString &filename=GLASSPLAYERHOST_DEFAULT_CONF_FILE);
  void save(const QString &filename=GLASSPLAYERHOST_DEFAULT_CONF_FILE) const;

 private:
  QString config_system_name;
  QString config_alsa_device;
  QString config_audio_device;
  QString config_stream_url;
};


#endif  // CONFIG_H
