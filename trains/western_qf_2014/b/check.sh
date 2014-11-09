#!/bin/bash

for((i=0;i<1000;++i)); do
    python gen.py > input.txt
    if ! ./b > o1; then
        echo Fail
        break
    fi
done
