set serveroutput on size 30000;

DECLARE
type VinothTable_t IS TABLE OF VinothTable%ROWTYPE; 
vinothTblVariable VinothTable_t;
BEGIN
select TSL.* BULK COLLECT INTO vinothTblVariable  from VinothTable TSL where id=1130592;

DBMS_OUTPUT.PUT_LINE(vinothTblVariable.COUNT);
DBMS_OUTPUT.PUT_LINE(vinothTblVariable(1).SLN_ID);

  FOR i IN vinothTblVariable.FIRST .. vinothTblVariable.LAST LOOP
    INSERT INTO VinothTable VALUES vinothTblVariable(i);
  END LOOP;

END;
/
