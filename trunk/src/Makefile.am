bin_PROGRAMS = billard3d

# set the include path found by configure
INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/math \
	-I$(top_srcdir)/src/assertion -I$(top_srcdir)/src/layers $(all_includes)

# the library search path.
billard3d_LDFLAGS = $(all_libraries) -lGL -lGLEW -lGLU -lSDL -lCg -lCgGL
AM_CXXFLAGS = -pedantic-errors -Wall
billard3d_SOURCES = bargmgr.cpp bautoeventlistener.cpp bball.cpp bband.cpp \
	bboard.cpp bcamera.cpp bconfig.cpp bconfigreader.cpp bconst.cpp bdraw.cpp \
	beventlistener.cpp bfont.cpp bfontmgr.cpp bfpstimer.cpp billard3d.cpp binput.cpp \
	blightmgr.cpp blockvector.cpp blogger.cpp blutable.cpp bmainloop.cpp bpath.cpp \
	bprofiler.cpp bsdlsystem.cpp bshader.cpp bsingleton.cpp bstatemachine.cpp bstream.cpp \
	bsystem.cpp btexture.cpp butils.cpp bvideo.cpp
SUBDIRS = math assertion layers
noinst_HEADERS = bargmgr.h bautoeventlistener.h bball.h bband.h bboard.h \
	bcamera.h bcg.h bconfig.h bconfigreader.h bconst.h bdraw.h beventlistener.h \
	bfont.h bfontmgr.h bfpstimer.h bgl.h binput.h blightmgr.h blockvector.h \
	blogger.h blutable.h bmainloop.h bpath.h bprofiler.h bsdl.h bsdlsystem.h \
	bshader.h bsingleton.h bstatemachine.h bstream.h bsystem.h btexture.h btypes.h \
	butils.h bvideo.h
billard3d_LDADD = $(top_builddir)/src/assertion/libbassertion.la \
	$(top_builddir)/src/math/libbmath.la $(top_builddir)/src/layers/libblayers.la
