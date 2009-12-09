/*
  checkpassword-mysql  -  checkpassword with mysql backend
  copyright 2008 2009 Thomas de Grivel

  checkpassword_mysql.c  -  core function

*/
#define _BSD_SOURCE 1
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "checkpassword_mysql.h"
#include "config.h"


static void run_prog (char * const prog[])
{
  execve (prog[0], prog, NULL);
  syslog (LOG_ERR, "execve failed\n");
  exit (111);
}


int checkpassword_mysql (const char *login,
                         const char *pass,
                         const char *time,
                         char * const prog[])
{
  MYSQL my;
  int num_rows;
  mysql_init (&my);
  if (!mysql_real_connect (&my,
                           CHECKPASSWORD_MYSQL_HOST,
                           CHECKPASSWORD_MYSQL_USER,
                           CHECKPASSWORD_MYSQL_PASS,
                           CHECKPASSWORD_MYSQL_DB,
                           CHECKPASSWORD_MYSQL_PORT,
                           CHECKPASSWORD_MYSQL_SOCKET,
                           0)) {
        syslog (LOG_ERR, "mysql_real_connect() failed: %s",
                mysql_error (&my));
        mysql_close (&my);
        exit (111);
  }
  {
    int len = strlen (login);
    char *escaped_login = calloc (len * 2 + 1, 1);
    mysql_real_escape_string (&my, escaped_login, login, len);

    len = strlen (pass);
    char *escaped_pass = calloc (len * 2 + 1, 1);
    mysql_real_escape_string (&my, escaped_pass, pass, len);

    len = strlen (CHECKPASSWORD_MYSQL_QUERY)
      + strlen (escaped_login) + strlen (escaped_pass);
    char *query = calloc(len + 1, 1);
    snprintf(query, len, CHECKPASSWORD_MYSQL_QUERY,
             escaped_login, escaped_pass);
    {
      int result = mysql_query (&my, query);
      if (result) {
        syslog (LOG_ERR, "mysql_query(\"%s\") failed (%i): %s",
                query, result, mysql_error (&my));
        mysql_close (&my);
        exit (111);
      }
    }
    {
      MYSQL_RES *res = mysql_store_result (&my);
      if (!res) {
        syslog (LOG_ERR, "mysql_store_result() failed: %s",
                mysql_error (&my));
        mysql_close (&my);
        exit (111);
      }
      num_rows = mysql_num_rows (res);
      mysql_free_result (res);
    }
  }
  mysql_close (&my);
  switch (num_rows) {
  case 0:
    exit (1);
  case 1:
    run_prog (prog);
  default:
    syslog (LOG_WARNING, "result has %i rows", num_rows);
    exit (111);
  }
  (void) time;
  return 0;
}
