

latestCoreFile=`ls -Art | tail -n 1`

coreFileName=$latestCoreFile
echo "Core File is $coreFileName"

binaryNameFromCoreFile=`file "$coreFileName" | awk -F \' '{print $2}'`
echo $binaryNameFromCoreFile


gdb -q --args $binaryNameFromCoreFile arg1 -c $coreFileName \
-ex "set pagination off" \
-ex bt \
-ex "thread apply all backtrace" \
-ex "info sharedlib" \
-ex "print "HAI"" \
-ex quit
