bin_PROGRAMS = billard3d
billard3d_SOURCES = bassert.cpp bball.cpp bballmgr.cpp bdraw.cpp bfpstimer.cpp \
	billard3d.cpp boutputmgr.cpp bsingleton.cpp butils.cpp bvector.cpp bvideo.cpp

# set the include path found by configure
INCLUDES = $(all_includes)

# the library search path.
billard3d_LDFLAGS = $(all_libraries) -lGL -lGLU -lSDL -lSDL_ttf
noinst_HEADERS = bassert.h bball.h bballmgr.h bdraw.h bfpstimer.h boutputmgr.h \
	bsingleton.h butils.h bvector.h bvideo.h
AM_CXXFLAGS = -pedantic-errors -Wall
