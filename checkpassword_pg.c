/*
  checkpassword-pg  -  checkpassword with postgresql backend
  copyright 2008 Thomas de Grivel

  checkpassword_pg.c  -  core function

*/
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <libpq-fe.h>
#include "checkpassword_pg.h"
#include "config.h"


static void run_prog (char * const prog[])
{
  execve (prog[0], prog, NULL);
  syslog (LOG_ERR, "execve failed\n");  
  exit (111);
}


int checkpassword_pg (const char *login,
                      const char *pass,
                      const char *time,
                      char * const prog[])
{
  PGconn        *conn;
  PGresult      *result;
  const char    *params[3];

  conn = PQconnectdb (CHKPW_PG_CONNINFO);
  if (!conn || PQstatus(conn) != CONNECTION_OK) {
    syslog (LOG_ERR, "PQconnectdb(\"%s\") failed (%p)\n",
	    CHKPW_PG_CONNINFO, (void*) conn);
    PQfinish (conn);
    exit (111);
  }

  params[0] = login;
  params[1] = pass;
  params[2] = time;
  result = PQexecParams (conn, CHKPW_PG_QUERY, 2, NULL, params, NULL, NULL, 0);
  if (PQresultStatus (result) != PGRES_TUPLES_OK) {
    syslog (LOG_ERR, "PQexecParams(\"%s\", \"%s\", \"%s\", \"%s\") failed: %s",
	    CHKPW_PG_QUERY, login, pass, time, PQresultErrorMessage (result));
    PQfinish (conn);
    exit (111);
  }

  switch (PQntuples (result)) {
  case 0:
    PQfinish (conn);
    exit (1);
  case 1:
    PQfinish (conn);
    run_prog (prog);
  default:
    PQfinish (conn);
    syslog (LOG_WARNING, "result has %i tuples", PQntuples (result));
    exit (111);
  }
  return 0;
}
