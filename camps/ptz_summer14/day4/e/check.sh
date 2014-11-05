#!/bin/bash

for((i=0;i<100;++i)); do
    echo $i
    python gen.py 67 21 > input.txt
    if ! ./e > /dev/null 2>/dev/null; then
        echo FAIL
        break
    fi
done
