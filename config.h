
#define CHKPW_PG_CONNINFO \
  "dbname='courier' user='courier' password='2R34lar.asd3r2.9/[qASwd'"


#define CHKPW_PG_QUERY \
  "SELECT id FROM passwd WHERE id=$1 AND clear=$2 LIMIT 1"
