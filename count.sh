#!/bin/bash

dir=.
if [ $# -gt 0 ]
then
    dir=$1
fi

hfiles=`find $1 -name "*.h" | wc -l`
ccfiles=`find $1 -name "*.cc" |  wc -l`

#  cmpccfiles=`find $1 -regex "^.+\.\(cc\|h\)" | grep "cc$" | wc -l`
#  cmphfiles=`find $1 -regex "^.+\.\(cc\|h\)" | grep "h$" | wc -l`

#  if [ $cmphfiles = $hfiles ]
#  then
#      echo ".h files count OK"
#  fi

#  if [ $cmpccfiles = $ccfiles ]
#  then
#      echo ".cc files count OK"
#  fi
allfiles=`find $1 -regex "^.+\.\(cc\|h\)" |  wc -l`

echo ".h file num: $hfiles"
echo ".cc file num: $ccfiles"
echo "all file num: $allfiles"
echo "all lines: `find $1 -regex "^.+\.\(cc\|h\)" | xargs wc -l | tail -n 1`"
