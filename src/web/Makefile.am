## automake.am
##
## Makefile.am for GlassPlayerHost web interface
##
## Use automake to process this into a Makefile.in
##
##   (C) Copyright 2016 Fred Gleason <fredg@paravelsystems.com>
##
##   This program is free software; you can redistribute it and/or modify
##   it under the terms of the GNU General Public License version 2 as
##   published by the Free Software Foundation.
##
##   This program is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
##
##   You should have received a copy of the GNU General Public
##   License along with this program; if not, write to the Free Software
##   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
##

AM_CPPFLAGS = -Wall -DPREFIX=\"$(prefix)\" @WEBHOST_CFLAGS@
MOC = @MOC@

# The dependency for qt's Meta Object Compiler (moc)
moc_%.cpp:	%.h
	$(MOC) $< -o $@

libexec_PROGRAMS = glassplayerhost.cgi

dist_glassplayerhost_cgi_SOURCES = cgicommands.h\
                                   glassplayerhost.cpp glassplayerhost.h\
                                   homepage.cpp homepage.h\
                                   playercontrol.cpp playercontrol.h\
                                   playerpage.cpp playerpage.h\
                                   statspage.cpp statspage.h\
                                   systemcontrol.cpp systemcontrol.h\
                                   systempage.cpp systempage.h\
                                   upgradecontrol.cpp upgradecontrol.h

nodist_glassplayerhost_cgi_SOURCES = config.cpp config.h

glassplayerhost_cgi_LDADD = @WEBHOST_LIBS@
##glassplayerhost_cgi_LDFLAGS =

localstate_DATA = glassplayer.js\
                  index.html\
                  ipsystem.js\
                  logo.png\
                  navbar.js\
                  player.js\
                  refresh.js\
                  stats.js\
                  utils.js

EXTRA_DIST = glassplayer.js\
             index.html\
             ipsystem.js\
             logo.png\
             navbar.js\
             player.js\
             refresh.js\
             stats.js\
             utils.js

CLEANFILES = *~\
             *.obj\
             *.idb\
             *.pdb\
             *ilk\
             moc_*

DISTCLEANFILES = config.cpp config.h

MAINTAINERCLEANFILES = *~\
                       Makefile.in
