lib_LTLIBRARIES = libfrozen-bubbles.la

libfrozen-bubbles_la_LIBADD = -lpthread
libfrozen-bubbles_la_LDFLAGS = -version-info 0:1:0
libfrozen-bubbles_la_CPPFLAGS = -O3 -std=c++11 -I../include

libfrozen-bubbles_la_SOURCES = \
./bubbles.cpp

bin_PROGRAMS = frozen-bubbles

frozen-bubbles_LDADD = -lpthread -lfrozen-bubbles
frozen-bubbles_LDFLAGS = -L.libs/
frozen-bubbles_CPPFLAGS = -O3 -std=c++11 -Wall -I../include

frozen-bubbles_SOURCES = \
./main.cpp
