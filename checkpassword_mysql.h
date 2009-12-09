/*
  checkpassword-mysql  -  checkpassword with mysql backend
  copyright 2008 2009 Thomas de Grivel

  checkpassword_mysql.h  -  core header

*/
#ifndef  CHECKPASSWORD_MYSQL_H
# define CHECKPASSWORD_MYSQL_H

int checkpassword_mysql (const char *login,
                         const char *pass,
                         const char *time,
                         char * const prog[]);

#endif
/* ndef  CHECKPASSWORD_MYSQL_H */
