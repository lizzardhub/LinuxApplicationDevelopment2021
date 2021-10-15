NCODE=$(echo | hexdump -v -e '/1 "%02X\n"')

row=0
col=0
while read -r line; do
  echo "$row $col $line"
  if [ "$line" == "$NCODE" ]; then
    let row=row+1
    col=0
  else
    let col=col+1
  fi
done