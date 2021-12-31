if [ $# -ne 0 ]
then
    echo "########### Updated file ############"
    echo $1 > /vinoth/etc/metaFiles/testName.txt
fi

V6_TEST_NAME=`cat /vinoth/etc/metaFiles/testName.txt`
