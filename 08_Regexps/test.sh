res=$(./esub "$1" "$2" "$3")
ans=$(echo "$3" | sed -E "s/$1/$2/")
echo "Res: \"$res\"; true ans: \"$ans\""
if [ "$ans" = "$res" ]; then
    exit 0
else
    exit 1
fi