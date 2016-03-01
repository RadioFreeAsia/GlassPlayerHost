// player.js
//
// Client-side player control routines for GlassPlayerHost.
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

var meta_socket;

function StartMetadata()
{
    meta_socket=
	new WebSocket('ws://'+location.hostname+'/','GlassPlayerMetadata');

    meta_socket.onmessage=function(event) {
	var metadata=JSON.parse(event.data);

	if((metadata.name=='StreamTitle')||
	   (metadata.name=='StreamUrl')) {
	    Id(metadata.name).innerHTML=metadata.value;
	}
	else {
	    var table=Id('ChannelFields');
	    var row=table.insertRow(table.rows.length);
	    var cell=row.insertCell(0);
	    cell.id=metadata.name+'Label';
	    cell.innerHTML=metadata.label;
	    cell=row.insertCell(1);
	    cell.id=metadata.name+'Value';
	    cell.innerHTML=metadata.value;
	}
    }
}
