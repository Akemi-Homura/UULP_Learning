#!/bin/zsh

res1=$(mktemp -t res1-XXXXXXXXX)
res2=$(mktemp -t res2-XXXXXXXXX)
trap 'rm -f $res1 $res2'

./pipe ls sort tail > $res1
ls | sort | tail > $res2

echo $res1:
cat $res1
echo $res2:
cat $res2

cmp=`comm -3 $res1 $res2`
if [ ${#cmp} -eq 0 ]
then
    echo Accept
else
    echo Failed
fi
