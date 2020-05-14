AM_CPPFLAGS = -I$(top_srcdir)/include
bin_PROGRAMS = SHServer
SHServer_SOURCES = main.c
SHServer_CFLAGS = $(PTHREAD_CFLAGS)
SHServer_LDADD = $(top_builddir)/lib/libshs.la $(PTHREAD_LIBS)
