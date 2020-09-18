create table V6PlayPartition
(
MyNumber NUMBER,
MyVarchar VARCHAR2(200),
myDate date,
myTimeStamp timestamp,
MyNumber2 NUMBER
)
PARTITION BY RANGE (MyNumber)
(
PARTITION RANGE_1_TO_100 VALUES LESS THAN (100),
PARTITION RANGE_100_TO_200 VALUES LESS THAN (200)
);



INSERT INTO V6PlayPartition (MyNumber,MyNumber2) VALUES(50,0);

INSERT INTO V6PlayPartition partition (RANGE_100_TO_200) (MyNumber,MyNumber2) VALUES(150,90);

SELECT * FROM  V6PlayPartition;
SELECT * FROM  V6PlayPartition partition (RANGE_100_TO_200) ;

DELETE  FROM V6PlayPartition;
DELETE  FROM V6PlayPartition partition (RANGE_100_TO_200) ;

