lib_LTLIBRARIES = libfrozen-bubbles.la

libfrozen_bubbles_la_LIBADD = -lpthread
libfrozen_bubbles_la_LDFLAGS = -version-info 0:1:0
libfrozen_bubbles_la_CPPFLAGS = -O3 -std=c++11 -I../include

libfrozen_bubbles_la_SOURCES = \
./bubbles.cpp

bin_PROGRAMS = frozen-bubbles

frozen_bubbles_LDADD = -lpthread -lfrozen-bubbles
frozen_bubbles_LDFLAGS = -L.libs/
frozen_bubbles_CPPFLAGS = -O3 -std=c++11 -Wall -I../include

frozen_bubbles_SOURCES = \
./main.cpp
