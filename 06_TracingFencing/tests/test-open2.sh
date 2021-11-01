# Mess up 4-th open call, when outfile is opened

rm -f myfile2.tmp
cp myfile1.back.tmp myfile1.tmp
testname=$(basename "$0") # get filename
testname="${testname#*-}" # split by -
testname="${testname%.*}" # split by .

strace -y -e trace=\!mmap,mprotect,munmap -e fault=open:when=4 -o strace-${testname}.log ./move myfile1.tmp myfile2.tmp
ret=$?
if [ "$ret" -ne "2" ]; then
    echo "Expected return code 2, got $ret"
    exit 1
fi
if [ ! -f "myfile1.tmp" ]; then
    echo "infile does not exist"
    exit 1
fi
if [ -f "myfile2.tmp" ]; then
    echo "outfile is still present"
    exit 1
fi
