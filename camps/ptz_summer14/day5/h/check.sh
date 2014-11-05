#!/bin/bash

for((i=0;i<100;++i)); do
    python gen.py > input.txt
    if ! ./h; then
        echo FAIL
        break
    fi
done
