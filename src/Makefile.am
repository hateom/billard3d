bin_PROGRAMS = billard3d
billard3d_SOURCES = bassert.cpp bball.cpp bballmgr.cpp bband.cpp bdraw.cpp \
	bfpstimer.cpp billard3d.cpp butils.cpp bvector.cpp bvideo.cpp

# set the include path found by configure
INCLUDES = $(all_includes)

# the library search path.
billard3d_LDFLAGS = $(all_libraries) -lGL -lGLU -lSDL -lSDL_ttf
noinst_HEADERS = bassert.h bball.h bballmgr.h bband.h bdraw.h bfpstimer.h \
	butils.h bvector.h bvideo.h
AM_CXXFLAGS = -pedantic-errors -Wall
