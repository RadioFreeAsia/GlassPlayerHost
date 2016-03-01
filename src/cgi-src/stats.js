// stats.js
//
// Client-side statistics routines for GlassPlayerHost.
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

var stat_socket;
var stat_socket_coount=0;

function StartStats()
{
    stat_socket=
	new WebSocket('ws://'+location.hostname+'/','GlassPlayerStats');

    stat_socket.onmessage=function(event) {
	var table;
	var row;
	var cell;
	var stats=JSON.parse(event.data);

	if(Id(stats.name+'Label')) {
	    cell=Id(stats.name+'Label');
	    cell.innerHTML='<strong>'+stats.label+'</strong>';
	    cell=Id(stats.name+'Value');
	    cell.innerHTML=stats.value;
	}
	else {
	    table=Id(stats.category+'Fields');
	    row=table.insertRow(table.rows.length);
	    cell=row.insertCell(0);
	    cell.id=stats.name+'Label';
	    cell.width=250;
	    cell.innerHTML='<strong>'+stats.label+'</strong>';
	    cell=row.insertCell(1);
	    cell.id=stats.name+'Value';
	    cell.innerHTML=stats.value;
	}

    }
}
