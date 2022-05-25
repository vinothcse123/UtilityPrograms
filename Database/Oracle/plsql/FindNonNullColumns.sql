
  SET serveroutput ON size 30000;
DECLARE
  schemaName varchar2(100) := 'MYSchemae';
  tableName varchar2(100) := 'MYtable';
  weekId NUMBER := 691;
  
  isPresent NUMBER;
  v_query   VARCHAR2(1000);
  v_errm    VARCHAR2(64);
  v_code    NUMBER;
TYPE columnNames_t
IS
  TABLE OF VARCHAR2(100);
  colNames columnNames_t;
BEGIN
  SELECT COLUMN_NAME BULK COLLECT
  INTO colNames
  FROM all_tab_columns
  WHERE TABLE_NAME LIKE UPPER(tableName)
  AND COLUMN_NAME LIKE 'colName%'
  AND OWNER LIKE schemaName
  ORDER BY COLUMN_ID;
  FOR colIdx IN 1 .. colNames.count
  LOOP
  BEGIN
    v_query:=
    'SELECT '|| colNames(colIdx) ||' FROM '|| schemaName || '.'||tableName ||' T  WHERE ROWNUM  =1 AND col IN ('||weekId||')'
    ;
    EXECUTE IMMEDIATE v_query INTO isPresent;
    IF isPresent IS NOT NULL THEN
      dbms_output.PUT_LINE(colNames(colIdx));
    END IF;
  EXCEPTION
  WHEN OTHERS THEN
    dbms_output.PUT_LINE('Exception');
    v_code := SQLCODE;
    v_errm := SUBSTR(SQLERRM, 1, 64);
    DBMS_OUTPUT.PUT_LINE (v_code || ' ' || v_errm);
  END;
  END LOOP;
  
END;
/
