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

function refreshMetadata()
{
    var http=GetXMLHttpRequest();
    if(http==null) {
	return;
    }

    //
    // Send the form
    //
    http.open("GET","/metadata.html",false);
    http.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
    http.send();

    //
    // Process the response
    //
    if(http.status==200) {
	Id('METADATA').innerHTML=http.responseText;
    }
    else {
	Id('METADATA').innerHTML=
	    '<table cellpadding="0" cellspacing="3" border="0" bgcolor="#FFFFFF" width="900">'+
	    '<tr><td>[no information available]</td></tr>'+
	    '</table>';
    }
}


function StartMetadata() {
    refreshMetadata();
    window.setInterval('refreshMetadata();',1000);
}
