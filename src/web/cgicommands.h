// cgicommands.h
//
// GlassPlayerHost CGI Configuration Interface
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

#ifndef CGICOMMANDS_H
#define CGICOMMANDS_H

//
// CGI Command Codes
// 
// FIXME: These must be kept in sync with the values in 'web/utils.js'.
//
#define CGI_COMMAND_SERVE_IPSETTINGS 1
#define CGI_COMMAND_COMMIT_IPSETTINGS 2
#define CGI_COMMAND_SERVE_GLASSPLAYER_CONFIG 3
#define CGI_COMMAND_COMMIT_GLASSPLAYER_CONFIG 4
#define CGI_COMMAND_UPLOAD_FIRMWARE 5
#define CGI_COMMAND_COMMIT_UPLOAD_FIRMWARE 6
#define CGI_COMMAND_SERVE_STATS 7

//
// Web Colors
//
// FIXME: These must be kept in sync with the values in 'web/utils.js'.
//
#define WEB_COLOR_BACKGROUND "#D4D0C8"
#define WEB_COLOR_PENDING "#FFFFFF"
#define WEB_COLOR_HEADER "#6383b7"
#define WEB_COLOR_DIALOG_HEADER "#D6D3CE"
#define WEB_COLOR_DIALOG_BACKGROUND "#C6C3C6"


#endif  // CGICOMMANDS_H
