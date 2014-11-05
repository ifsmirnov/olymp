#!/bin/bash

for((i=0;i<100;++i)); do
    python gen.py > input.txt
    if ! ./f2; then
        echo FAIL
        break
    fi
done
