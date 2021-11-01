rm -f myfile2.tmp
cp myfile1.back.tmp myfile1_PROTECT.tmp

LD_PRELOAD="$PWD/libremove.so" ./move myfile1_PROTECT.tmp myfile2.tmp
diff myfile1.back.tmp myfile2.tmp
if [ "$?" -ne "0" ]; then
    echo "Files differ after moving"
    exit 1
fi