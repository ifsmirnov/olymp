#!/bin/bash

for((i=0;i<1000;++i)); do
#     if ((i%100)); then
        echo $i
#     fi
    ./gen 106 3
    if ! ./e > /dev/null; then
        echo FAIL
        break
    fi
done
