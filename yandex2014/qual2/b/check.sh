#!/bin/bash

for((i=0;i<100;++i)); do
    python gen.py 5 10 > input.txt
    if ! ./b; then
        echo Fail
        break
    fi
done
