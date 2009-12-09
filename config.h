
#define CHECKPASSWORD_MYSQL_HOST                \
  "localhost"

#define CHECKPASSWORD_MYSQL_USER                \
  "vmail"

#define CHECKPASSWORD_MYSQL_PASS                \
  "23.fTh-e+r3Dq3/eiAu.r2Vy3rD"

#define CHECKPASSWORD_MYSQL_DB                  \
  "vmail"

#define CHECKPASSWORD_MYSQL_PORT                \
  0

#define CHECKPASSWORD_MYSQL_SOCKET              \
  NULL

#define CHECKPASSWORD_MYSQL_QUERY                                       \
  "SELECT id FROM accounts WHERE CONCAT(id,'@',domain)='%s' AND clearpass='%s' LIMIT 1"

#define CHECKPASSWORD_MYSQL_DEBUG               \
  1
