hexdump -v -e '/1 "%02X\n"' < /dev/stdin | ./numerator.sh | shuf | ./printer.sh $1
#hexdump -C < /dev/stdin
exit

echo "Hello world!"
echo "$0 $1"

# echo Hello, who am I talking to?
# read varname
# echo It\'s nice to meet you $varname

# foo=abcde
# for (( i=0; i<${#foo}; i++ )); do
#   echo "${foo:$i:1}"
# done
# exit

NEWLINE="
"

tput clear
i=0
tput sc
text=""
while read -r line; do
  tput clear
  tput rc
#   for (( i=0; i<${#line}; i++ )); do
#     #echo "${foo:$i:1}"
#     text+="${line:$i:1}\n"
#   done
  cmd=$(echo ${line} | od -w1 -c -v -An)
  if [ -z "$text" ]; then
    text="$cmd"
  else
    text="$text$NEWLINE$cmd" 
  fi
#   echo "line$((i=i+1))"
#   echo "line$((i=i+1))"
#   echo "line$((i=i+1))"
#   echo "line$((i=i+1))"
done
#echo "${text}"
cmd=$(echo "${text}" | ./numerator.sh)
echo "${cmd}"
