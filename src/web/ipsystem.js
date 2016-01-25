// ipsystem.js
//
// Client-side routines for IP Systems of GlassPlayerHost web interface.
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

//
// IP Settings Callbacks
//
function validateIpSettings() {
    var addr_err='<font color=\"#FF0000\">INVALID ADDRESS</font>';
    var mask_err='<font color=\"#FF0000\">INVALID NETMASK</font>';
    var ok=true;
    var name_format=0;
    var source_sort_order=0;
    var destination_sort_order=0;

    if(!ValidateAddress(Id("IP_ADDRESS").value)) {
	Id("IP_ADDRESS_ERR").innerHTML=addr_err;
	ok=false;
    }
    else {
	Id("IP_ADDRESS_ERR").innerHTML="&nbsp";
    }
    if(!ValidateAddress(Id("IP_NETMASK").value)) {
	Id("IP_NETMASK_ERR").innerHTML=addr_err;
	ok=false;
    }
    else {
      	Id("IP_NETMASK_ERR").innerHTML="&nbsp";
    }
    if(!ValidateGateway(Id("IP_GATEWAY").value)) {
	Id("IP_GATEWAY_ERR").innerHTML=mask_err;
	ok=false;
    }
    else {
      	Id("IP_GATEWAY_ERR").innerHTML="&nbsp";
    }
    if(Id("IP_DNS1").value=="") {
	Id("IP_DNS1").innerHTML="0.0.0.0";
      	   Id("IP_DNS1_ERR").innerHTML="&nbsp";
    }
    else {
	if(!ValidateAddress(Id("IP_DNS1").value)) {
	    Id("IP_DNS1_ERR").innerHTML=addr_err;
	    ok=false;
	}
	else {
      	    Id("IP_DNS1_ERR").innerHTML="&nbsp";
	}
    }
    if(!ValidateAddress(Id("IP_DNS2").value)) {
	Id("IP_DNS2_ERR").innerHTML=addr_err;
	ok=false;
    }
    else {
      	Id("IP_DNS2_ERR").innerHTML="&nbsp";
    }
    if(Id("PASSWORD1").value!=Id("PASSWORD2").value) {
	Id("PASSWORD_ERR").innerHTML="<font color=\"#FF0000\">The passwords do not match!</font>";
	ok=false;
    }
    else {
      	Id("PASSWORD_ERR").innerHTML="&nbsp"; 
    }

    //
    // Post the form
    //
    if(ok) {
	var form='';
	form+='COMMAND='+CGI_COMMAND_COMMIT_IPSETTINGS;
	form+='&IP_ADDRESS='+UrlEncode(Id("IP_ADDRESS").value);
	form+='&IP_NETMASK='+UrlEncode(Id("IP_NETMASK").value);
	form+='&IP_GATEWAY='+UrlEncode(Id("IP_GATEWAY").value);
	form+='&IP_DNS1='+UrlEncode(Id("IP_DNS1").value);
	form+='&IP_DNS2='+UrlEncode(Id("IP_DNS2").value);
	form+='&PASSWORD='+UrlEncode(Id("PASSWORD1").value);
	form+='&TIME_ZONE='+UrlEncode(Id("TIME_ZONE").value);
	form+='&NTP_ADDRESS0='+UrlEncode(Id("NTP_ADDRESS0").value);
	form+='&NTP_ADDRESS1='+UrlEncode(Id("NTP_ADDRESS1").value);
	PostForm(form,'/cgi-bin/glassplayerhost.cgi');
    }
}

function downloadConfig() {
    var form='COMMAND='+CGI_COMMAND_DOWNLOAD_CONFIG;
    PostForm(form,'/cgi-bin/glassplayerhost.cgi');
}
