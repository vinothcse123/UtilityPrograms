
latestCoreFile=`ls -Art | tail -n 1`

coreFileName=$latestCoreFile
echo "Core File is $coreFileName"

gdb -q  $coreFileName \
-ex set pagination off \
-ex bt \
-ex thread apply all backtrace \
-ex quit
