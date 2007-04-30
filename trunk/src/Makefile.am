bin_PROGRAMS = billard3d
billard3d_SOURCES = bassert.cpp bball.cpp bballmgr.cpp bband.cpp bdraw.cpp \
	bexceptionstream.cpp bfont.cpp bfontmgr.cpp bfpstimer.cpp billard3d.cpp blogger.cpp \
	blutable.cpp bpath.cpp bsingleton.cpp btexture.cpp btrace.cpp butils.cpp bvector.cpp \
	bvideo.cpp

# set the include path found by configure
INCLUDES = $(all_includes)

# the library search path.
billard3d_LDFLAGS = $(all_libraries) -lGL -lGLU -lSDL -lSDL_ttf
noinst_HEADERS = bassert.h bball.h bballmgr.h bband.h bdraw.h \
	bexceptionstream.h bfpstimer.h blogger.h blutable.h bpath.h bsingleton.h btrace.h butils.h \
	bvector.h bvideo.h
AM_CXXFLAGS = -pedantic-errors -Wall
