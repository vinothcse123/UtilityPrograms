end=20
for ((i=1;i<=end;i++)); do
./roc.ksh 1014
ret=$?
#
#  returns > 127 are a SIGNAL
#
if [ $ret -gt 127 ]; then
        sig=$((ret - 128))
        echo "========================>Got SIGNAL $sig"
        if [ $sig -eq $(kill -l SIGKILL) ]; then
                echo "=======================================>process was killed with SIGKILL"
                dmesg -T> dmesg-kill.log
        fi
fi
done
