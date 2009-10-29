/*
  checkpassword-pg  -  checkpassword with postgresql backend
  copyright 2008 Thomas de Grivel

  checkpassword_pg.h  -  core header

*/
#ifndef  CHECKPASSWORD_PG_H
# define CHECKPASSWORD_PG_H

int checkpassword_pg (const char *login,
                      const char *pass,
                      const char *time,
                      char * const prog[]);

#endif
/* ndef  CHECKPASSWORD_PG_H */
