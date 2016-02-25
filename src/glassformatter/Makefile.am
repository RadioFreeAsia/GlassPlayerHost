## automake.am
##
## Makefile for the glassformatter(1) stats processor for glassplayer(1).
##
## (C) Copyright 2014-2015 Fred Gleason <fredg@paravelsystems.com>
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
##
## Use automake to process this into a Makefile.in

AM_CPPFLAGS = -Wall -DPREFIX=\"$(prefix)\" -Wno-strict-aliasing @QT4_CFLAGS@ @WEBHOST_CFLAGS@
MOC = @QT4_MOC@

# The dependency for qt's Meta Object Compiler (moc)
moc_%.cpp:	%.h
	@MOC@ $< -o $@


bin_PROGRAMS = glassformatter

dist_glassformatter_SOURCES = glassformatter.cpp glassformatter.h\
                              statsstore.cpp statsstore.h\
                              statsvalues.cpp statsvalues.h

nodist_glassformatter_SOURCES = config.cpp config.h\
                                moc_glassformatter.cpp

glassformatter_LDADD = @SIRLIBS@ @WEBHOST_LIBS@
glassformatter_LDFLAGS = @SIRFLAGS@

CLEANFILES = *~\
             moc_*\
             *.obj\
             *.idb\
             *.pdb\
             *ilk

DISTCLEANFILES = config.cpp config.h\
                 paths.h

MAINTAINERCLEANFILES = *~\
                       Makefile.in
