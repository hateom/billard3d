INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/math \
	-I$(top_srcdir)/src/assertion -I$(top_srcdir)/src/layers $(all_includes)
METASOURCES = AUTO
noinst_LTLIBRARIES = libblayers.la
libblayers_la_SOURCES = bconsteditlogiclayer.cpp bconsteditvideolayer.cpp \
	blayermgr.cpp blogiclayer.cpp boptionslogiclayer.cpp boptionsvideolayer.cpp \
	bpauselogiclayer.cpp bpausevideolayer.cpp bsimlogiclayer.cpp bsimvideolayer.cpp \
	bsynclogiclayer.cpp bsyncvideolayer.cpp bvideolayer.cpp
libblayers_la_LIBADD = $(top_builddir)/src/assertion/libbassertion.la \
	$(top_builddir)/src/math/libbmath.la
