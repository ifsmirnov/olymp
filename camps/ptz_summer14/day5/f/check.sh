#!/bin/bash

for((i=0;i<100;++i)); do
    python gen.py 10000 > input.txt
    break
    if ! ./f > /dev/null; then
        echo FAIL
        break
    fi
done
