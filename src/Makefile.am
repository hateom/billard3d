bin_PROGRAMS = billard3d
billard3d_SOURCES = bball.cpp bballmgr.cpp bdraw.cpp billard3d.cpp bvector.cpp \
	bvideo.cpp

# set the include path found by configure
INCLUDES = $(all_includes)

# the library search path.
billard3d_LDFLAGS = $(all_libraries) -lGL -lGLU -lSDL
noinst_HEADERS = bball.h bballmgr.h bdraw.h bvector.h bvideo.h
AM_CXXFLAGS = -pedantic-errors -Wall
