#!/bin/bash

who | sort > prev
while true
do
    sleep 1
    who | sort > curr
    loggout=`comm -23 prev curr`
    login=`comm -13 prev curr`
    if [ ${#loggout} -gt 0 ]
    then
        echo "loggout out: "
        echo $loggout
    fi
    if [ ${#login} -gt 0 ]
    then
        echo "logged in: "
    fi
    mv curr prev
done
