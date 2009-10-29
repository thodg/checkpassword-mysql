
##  settings

prefix = /usr/local

CC = gcc
INSTALL = install
DEBUG_CFLAGS = -O0 -ggdb
RELEASE_CFLAGS = -O2 -g
CFLAGS += -W -Wall -Werror -ansi -pedantic ${DEBUG_CFLAGS}
CPPFLAGS += -I${prefix}/include/postgresql83
LDFLAGS += -L${prefix}/lib/postgresql83
LIBS = -lpq

HEADERS = \
	checkpassword_pg.h \
	config.h

SOURCES = \
	checkpassword_pg.c \
	cli.c \
	log.c

OBJECTS = ${SOURCES:.c=.o}

all: checkpassword-pg

##  install

install: checkpassword-pg
	${INSTALL} -m 0755 $< ${prefix}/bin

##  dist

VERSION = 0.1
DIST = checkpassword_pg-$(VERSION)
dist:
	svn export . ${DIST}
	tar czf ${DIST}.tar.gz ${DIST}
	rm -rf ${DIST}

##  clean

CLEANFILES = *.o checkpassword-pg
CLEANFILES_ = $(wildcard ${CLEANFILES})
clean:
	test -z ${CLEANFILES_} || rm -f ${CLEANFILES}

##  build

checkpassword-pg: ${OBJECTS} ${HEADERS} Makefile
	${CC} -o $@ ${CFLAGS} ${LDFLAGS} ${OBJECTS} ${LIBS}

%.o: %.c ${HEADERS} Makefile
	${CC} ${CFLAGS} ${CPPFLAGS} -c $<
