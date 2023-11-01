
CONN_STRING="dddd/dddd@DBDe1"

sqlplus -S $CONN_STRING    << EOF47
   select sysdate from dual;
EOF47
