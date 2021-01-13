--Global Temporary table
-- Temporary table will not be dropped at end of session, where as data inserted in one session is not visible to others.

CREATE GLOBAL TEMPORARY TABLE V6PlayTempTable
(
MyNumber NUMBER,
MyVarchar VARCHAR2(200),
myDate date,
myTimeStamp timestamp,
myFloat NUMBER,
MyNumber2 NUMBER
)
ON COMMIT PRESERVE ROWS; 


INSERT INTO V6PlayTempTable(MYNUMBER,MYVARCHAR) VALUES(100,'VINOTH');
INSERT INTO V6PlayTempTable(MYNUMBER,MYVARCHAR) VALUES(200,'KIRUBA');
INSERT INTO V6PlayTempTable(MYNUMBER,MYVARCHAR) VALUES(300,'PAVAN KARTHI GV');
INSERT INTO V6PlayTempTable(MYDATE) VALUES(to_date('10-DEC-21 10:34:33','yyyy/mm/dd hh24:mi:ss'));

                                 
DELETE FROM V6PlayTempTable;COMMIT;
         
SELECT * FROM V6PlayTempTable;

