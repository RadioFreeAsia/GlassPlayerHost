// config.cpp
//
// Class for reading GlassPlayerHost configuration.
//
// (C) Copyright 2016 Fred Gleason <fredg@paravelsystems.com>
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

#include <wh/whprofile.h>

#include "config.h"

Config::Config()
{
}


QString Config::alsaDevice() const
{
  return config_alsa_device;
}


void Config::setAlsaDevice(const QString &str)
{
  config_alsa_device=str;
}


QString Config::audioDevice() const
{
  return config_audio_device;
}


void Config::setAudioDevice(const QString &str)
{
  config_audio_device=str;
}


QString Config::streamUrl() const
{
  return config_stream_url;
}


void Config::setStreamUrl(const QString &str)
{
  config_stream_url=str;
}


void Config::load(const QString &filename)
{
  WHProfile *p=new WHProfile();

  p->setSource(filename);
  config_alsa_device=p->stringValue("GlassPlayerHost","AlsaDevice","hw:0");
  config_audio_device=p->stringValue("GlassPlayerHost","AudioDevice","ALSA");
  config_stream_url=p->stringValue("GlassPlayerHost","StreamUrl");
  delete p;
}


void Config::save(const QString &filename) const
{
  FILE *f=NULL;

  if((f=fopen((filename+"-back").toUtf8(),"w"))!=NULL) {
    fprintf(f,"[GlassPlayerHost]\n");
    fprintf(f,"AlsaDevice=%s\n",(const char *)config_alsa_device.toUtf8());
    fprintf(f,"AudioDevice=%s\n",(const char *)config_audio_device.toUtf8());
    fprintf(f,"StreamUrl=%s\n",(const char *)config_stream_url.toUtf8());
    fclose(f);
    rename((filename+"-back").toUtf8(),filename.toUtf8());
  }
}
