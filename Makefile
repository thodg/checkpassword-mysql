
##  settings

prefix = /opt/local

CC = gcc
INSTALL = install
DEBUG_CFLAGS = -O0 -ggdb
RELEASE_CFLAGS = -O2 -g
CFLAGS += -W -Wall -Werror -ansi ${DEBUG_CFLAGS}
CPPFLAGS += -I${prefix}/include/mysql5
LDFLAGS += -L${prefix}/lib/mysql5
LIBS = -lmysqlclient

HEADERS = \
	checkpassword_mysql.h \
	config.h

SOURCES = \
	checkpassword_mysql.c \
	cli.c

OBJECTS = ${SOURCES:.c=.o}

all: checkpassword-mysql

##  install

install: checkpassword-mysql
	${INSTALL} -m 0755 $< ${prefix}/bin

##  dist

VERSION = 0.1
DIST = checkpassword_mysql-$(VERSION)
dist:
	svn export . ${DIST}
	tar czf ${DIST}.tar.gz ${DIST}
	rm -rf ${DIST}

##  clean

CLEANFILES = *.o checkpassword-mysql
CLEANFILES_ = $(wildcard ${CLEANFILES})
clean:
	test -z ${CLEANFILES_} || rm -f ${CLEANFILES}

##  build

checkpassword-mysql: ${OBJECTS} ${HEADERS} Makefile
	${CC} -o $@ ${CFLAGS} ${LDFLAGS} ${OBJECTS} ${LIBS}

%.o: %.c ${HEADERS} Makefile
	${CC} ${CFLAGS} ${CPPFLAGS} -c $<
