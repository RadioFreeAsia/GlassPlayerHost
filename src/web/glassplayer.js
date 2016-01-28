// glassplayer.js
//
// Client-side GlassPlayer interface for GlassPlayerHost
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

function applyGlassPlayerSettings()
{
    var form='';
    form+='COMMAND='+CGI_COMMAND_COMMIT_GLASSPLAYER_CONFIG;
    form+='&RECEIVER_NAME='+Escape(Id('RECEIVER_NAME').value);
    form+='&STREAM_URL='+Escape(Id('STREAM_URL').value);
    PostForm(form,'/cgi-bin/glassplayerhost.cgi');
}
