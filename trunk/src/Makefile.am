bin_PROGRAMS = billard3d
billard3d_SOURCES = bassert.cpp bball.cpp bballmgr.cpp bband.cpp bboard.cpp \
	bconfig.cpp bconfigreader.cpp bdraw.cpp beventlistener.cpp bexception.cpp \
	bexceptionstream.cpp bfont.cpp bfontmgr.cpp bfpstimer.cpp billard3d.cpp binput.cpp \
	blogger.cpp blogiclayer.cpp blutable.cpp bmainloop.cpp bpath.cpp \
	bpauselogiclayer.cpp bpausevideolayer.cpp bprofiler.cpp bsdlsystem.cpp bsimlogiclayer.cpp \
	bsimvideolayer.cpp bsingleton.cpp bstatemachine.cpp bsystem.cpp btexture.cpp btrace.cpp \
	butils.cpp bvector.cpp bvideo.cpp bvideolayer.cpp

# set the include path found by configure
INCLUDES = $(all_includes)

# the library search path.
billard3d_LDFLAGS = $(all_libraries) -lGL -lGLU -lSDL -lSDL_ttf
noinst_HEADERS = bassert.h bball.h bballmgr.h bband.h bboard.h bconfig.h \
	bconfigreader.h bdraw.h beventlistener.h bexception.h bexceptionstream.h bfpstimer.h \
	binput.h blogger.h blogiclayer.h blutable.h bmainloop.h bpath.h \
	bpauselogiclayer.h bpausevideolayer.h bprofiler.h bsdlsystem.h bsimlogiclayer.h \
	bsimvideolayer.h bsingleton.h bstatemachine.h bsystem.h btrace.h butils.h bvector.h \
	bvideo.h bvideolayer.h
AM_CXXFLAGS = -pedantic-errors -Wall
