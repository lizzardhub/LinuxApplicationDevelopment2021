head -c 1000 </dev/urandom >testfile.tmp
echo "Test file generated"

success=true

echo "Test CRC32 (hex output)"
hash=$(rhash --uppercase --simple --crc32 testfile.tmp)
stringarray=($hash)
hash=${stringarray[0]}
out=$(echo "CRC32 testfile.tmp" | ./rhasher)
if [ "$hash" != "$out" ]; then
    printf "Hashes differ!\ncorrect: %s\noutput: %s\n" "$hash" "$out"
    success=false
fi

echo "Test SHA1 (hex output)"
hash=$(rhash --uppercase --simple --sha1 testfile.tmp)
stringarray=($hash)
hash=${stringarray[0]}
out=$(echo "SHA1 testfile.tmp" | ./rhasher)
if [ "$hash" != "$out" ]; then
    printf "Hashes differ!\ncorrect: %s\noutput: %s\n" "$hash" "$out"
    success=false
fi

echo "Test SHA3-512 (hex output)"
hash=$(rhash --uppercase --simple --sha3-512 testfile.tmp)
stringarray=($hash)
hash=${stringarray[0]}
out=$(echo "SHA3-512 testfile.tmp" | ./rhasher)
if [ "$hash" != "$out" ]; then
    printf "Hashes differ!\ncorrect: %s\noutput: %s\n" "$hash" "$out"
    success=false
fi

echo "Test MD5 (base64 output)"
hash=$(rhash --printf=%B{md5} testfile.tmp)
stringarray=($hash)
hash=${stringarray[0]}
out=$(echo "md5 testfile.tmp" | ./rhasher)
if [ "$hash" != "$out" ]; then
    printf "Hashes differ!\ncorrect: %s\noutput: %s\n" "$hash" "$out"
    success=false
fi

if [ $success = true ]; then
    echo "All tests passed successfully"
else
    echo "Tests failed"
    exit 1
fi