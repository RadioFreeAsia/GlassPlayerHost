// utils.js
//
// Client-side utility routines for GlassPlayerHost.
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
// CGI Operations
//
// FIXME: These must be kept in sync with the values in 'web/cgicommands.h'.
//
CGI_COMMAND_SERVE_IPSETTINGS=1;
CGI_COMMAND_COMMIT_IPSETTINGS=2;
CGI_COMMAND_SERVE_GLASSPLAYER_CONFIG=3;
CGI_COMMAND_COMMIT_GLASSPLAYER_CONFIG=4;
CGI_COMMAND_UPLOAD_FIRMWARE=5;
CGI_COMMAND_COMMIT_UPLOAD_FIRMWARE=6;

//
// Web Colors
//
// FIXME: These must be kept in sync with the values in 'web/cgicommands.h'.
//
WEB_COLOR_BACKGROUND='#D4D0C8';
WEB_COLOR_PENDING='#FFFFFF';
WEB_COLOR_HEADER='#6383b7';
WEB_COLOR_DIALOG_HEADER='#D6D3CE';
WEB_COLOR_DIALOG_BACKGROUND='#C6C3C6';


function PostForm(form,url)
{
    var http=GetXMLHttpRequest();
    if(http==null) {
	return;
    }

    //
    // Send the form
    //
    http.open("POST",url,false);
    http.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
    http.send(form);

    //
    // Process the response
    //
    if(http.status==200) {
	var html=http.responseText;
	document.open();
	document.write(html);
	document.close();
    }
    else {
	alert('Status: '+http.status+'  HTML: '+http.responseText);
    }
}

function SendForm(form,url)
{
    var http=GetXMLHttpRequest();
    if(http==null) {
	return;
    }

    //
    // Send the form
    //
    http.open("POST",url,true);
    http.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
    http.send(form);
}

function IsIE() {
    return !document.implementation.hasFeature("Events","2.0");
}

function TestXMLText(tag,n,obj) {
    return obj.getElementsByTagName(tag).length>n;
}

function GetXMLText(tag,n,obj) {
    if(obj.getElementsByTagName(tag).length>n) {
	if(obj.getElementsByTagName(tag)[n].childNodes.length>0) {
	    /*
	    alert('len: '+obj.getElementsByTagName(tag)[n].childNodes.length);
	    for(var i=0;i<obj.getElementsByTagName(tag)[n].childNodes.length;i++) {
		alert('nodeName: '+obj.getElementsByTagName(tag)[n].childNodes[0].nodeName);
		alert('nodeType: '+obj.getElementsByTagName(tag)[n].childNodes[0].nodeType);
	    }
	    */
	    return obj.getElementsByTagName(tag)[n].childNodes[0].nodeValue;
	}
    }
    return null;
}

function Id(id) {
    return document.getElementById(id);
}

function AddOption(list,option) {
    for(var i=0;i<list.length;i++) {
	if(option.value.localeCompare(list.options[i].value)<0) {
	    list.add(option,list.options[i]);
	    return;
	}
    }
    list.add(option,null);
}

var http_factory=null;
var http_factories=[
    function() {
	return new XMLHttpRequest();
    },
    function() {
	return new ActiveXObject("Microsoft.XMLHTTP");
    },
    function() {
	return new ActiveXObject("MSXML2.XMLHTTP.3.0");
    },
    function() {
	return new ActiveXObject("MSXML2.XMLHTTP");
    }
];

function GetXMLHttpRequest() {
    for(var i=0;i<http_factories.length;i++) {
	try {
	    var factory=http_factories[i];
	    var request=factory();
	    if(request!=null) {
		http_factory=factory;
		return request;
	    }
	}
	catch(e) {
	    continue;
	}
    }
    return null;
}

function UrlEncode(str) {
    var ret=new String;

    for(i=0;i<str.length;i++) {
	switch(str.charAt(i)) {
	case '$':
	case '&':
	case '+':
	case ',':
	case '/':
	case ':':
	case ';':
	case '=':
	case '?':
	case '@':
	case ' ':
	case '"':
	case '<':
	case '>':
	case '#':
	case '%':
	case '{':
	case '}':
	case '|':
	case '\\':
	case '^':
	case '~':
	case '[':
	case ']':
	case '`':
	    ret+=EncodeChar(str.charCodeAt(i));
	    break;

	default:
	    if((str.charCodeAt(i)<0x20)||(str.charCodeAt(i)>=0x7F)) {
		ret+=EncodeChar(str.charCodeAt(i));
	    }
	    else {
		ret+=str.charAt(i);
	    }
	    break;
	}
    }
    return ret;
}

function EncodeChar(c) {
    var ret=new String;
    ret="%";
    if(c<16) {
	ret+="0";
    }
    ret+=c.toString(16);
    return ret;
}

function ValidateAddress(addr) {
    str=new String;

    list=new Array;
    list=addr.split(".");
    if(list.length!=4) {
	return false;
    }
    for(i=0;i<4;i++) {
	if((list[i].length==0)||(list[i]<0)||(list[i]>255)) {
	    return false;
	}
    }
    return true;
}

function ValidateGateway(addr) {
    if(addr.length==0) {
	return true;
    }

    str=new String;

    list=new Array;
    list=addr.split(".");
    if(list.length!=4) {
	return false;
    }
    for(i=0;i<4;i++) {
	if((list[i].length==0)||(list[i]<0)||(list[i]>255)) {
	    return false;
	}
    }
    return true;
}

function Escape(str) {
    ret=new String;

    for(i=0;i<str.length;i++) {
	if(str.charAt(i)=='!') {
	    ret+='\\';
	}
	ret+=str.charAt(i);
    }

    return ret;
}
