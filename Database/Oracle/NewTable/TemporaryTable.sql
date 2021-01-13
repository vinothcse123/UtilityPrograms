--Global Temporary table
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


