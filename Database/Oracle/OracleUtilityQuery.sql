

--H:Table




--H:column

--constraints of column
select * from all_constraints where table_name like 'MRVL_INPUT_FACT';

--Column related characteritics
SELECT *
FROM ALL_TAB_COLUMNS
WHERE TABLE_NAME LIKE 'TRVL_INPUT_FACT%'
AND COLUMN_NAME LIKE '%INF_SOURCE%';


--H:session

select * from v$session;


--statistics of session
select * from v$mystat;
