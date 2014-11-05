#!/bin/bash

for((i=0;i<1000;++i)); do
    if ((i%10==0)); then
        echo $i
    fi
    ./gen 100 20 $RANDOM > input.txt
    if ! ./h > o1; then
        echo FAIL1
        break
    fi
    if ! ./h2 > o2; then
        echo FAIL2
        break
    fi
    if ! diff -q o1 o2; then
        echo FAIL
        break
    fi
done
