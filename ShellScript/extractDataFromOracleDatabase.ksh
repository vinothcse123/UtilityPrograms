
FD_ID=1124342
CONN_STRING="dddd/dddd@DBDe1"
set colsep
sqlplus -S $CONN_STRING    << EOF47
    SET COLSEP ',';
    SET LINESIZE 32767;
    SET UNDERLINE OFF;
   select mycol from table T where T.fd IN ( $FD_ID ) FETCH FIRST 1 ROW ONLY;
EOF47
