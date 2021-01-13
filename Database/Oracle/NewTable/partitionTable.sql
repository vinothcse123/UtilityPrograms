create table V6PlayPartition
(
MyNumber NUMBER,
MyVarchar VARCHAR2(200),
myDate date,
myTimeStamp timestamp,
myFloat NUMBER,
MyNumber2 NUMBER
)
PARTITION BY RANGE (MyNumber)
(
PARTITION RANGE_1_TO_100K VALUES LESS THAN (100000),
PARTITION RANGE_200K_TO_200K VALUES LESS THAN (200000)
);


-- partioned index
-- It creates partition index on table with partition info provided while creating table
CREATE INDEX V6PlayPartition_idx ON V6PlayPartition(MyNumber) LOCAL;

DROP TABLE V6PlayPartition;

INSERT INTO V6PlayPartition (MyNumber,MyNumber2) VALUES(50,0);

INSERT INTO V6PlayPartition partition (RANGE_1_TO_100K) (MyNumber,MyNumber2) VALUES(150,90);

SELECT * FROM  V6PlayPartition;
SELECT * FROM  V6PlayPartition partition (RANGE_1_TO_100K) ;

DELETE  FROM V6PlayPartition;
DELETE  FROM V6PlayPartition partition (RANGE_1_TO_100K) ;
