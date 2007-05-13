bin_PROGRAMS = billard3d
billard3d_SOURCES = GLquat.c bargmgr.cpp bassert.cpp bautoeventlistener.cpp \
	bball.cpp bband.cpp bboard.cpp bconfig.cpp bconfigreader.cpp bdraw.cpp \
	berrortrace.cpp beventlistener.cpp bexception.cpp bfont.cpp bfontmgr.cpp bfpstimer.cpp \
	billard3d.cpp binput.cpp blightmgr.cpp blockvector.cpp blogger.cpp blogiclayer.cpp \
	blutable.cpp bmainloop.cpp bpath.cpp bpauselogiclayer.cpp bpausevideolayer.cpp \
	bprofiler.cpp bquaternion.cpp bsdlsystem.cpp bsimlogiclayer.cpp bsimvideolayer.cpp \
	bsingleton.cpp bstatemachine.cpp bstream.cpp bsystem.cpp btexture.cpp btrace.cpp \
	butils.cpp bvector.cpp bvideo.cpp bvideolayer.cpp

# set the include path found by configure
INCLUDES = $(all_includes)

# the library search path.
billard3d_LDFLAGS = $(all_libraries) -lGL -lGLU -lSDL -lGLEW
noinst_HEADERS = bargmgr.h bassert.h bautoeventlistener.h bball.h bband.h \
	bboard.h bconfig.h bconfigreader.h bdraw.h berrortrace.h beventlistener.h \
	bexception.h bfpstimer.h binput.h blightmgr.h blogger.h blogiclayer.h blutable.h \
	bmainloop.h bpath.h bpauselogiclayer.h bpausevideolayer.h bprofiler.h bquaternion.h \
	bsdlsystem.h bsimlogiclayer.h bsimvideolayer.h bsingleton.h bstatemachine.h \
	bsystem.h btrace.h butils.h bvector.h bvideo.h bvideolayer.h
AM_CXXFLAGS = -pedantic-errors -Wall
