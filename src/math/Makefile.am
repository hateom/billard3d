CXXFLAGS = -DDATADIR='"$(datadir)"' @CXXFLAGS@

INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/math \
	-I$(top_srcdir)/src/assertion $(all_includes)
METASOURCES = AUTO
noinst_LTLIBRARIES = libbmath.la
libbmath_la_SOURCES = bquaternion.cpp bsincos.cpp bvector.cpp bvector3.cpp
