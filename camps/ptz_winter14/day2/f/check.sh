#!/bin/bash

for((i=0;i<1000;++i)); do
    perl gen.pl 400 500 > input.txt
    if ! ./f; then
        echo FAIL
        break
    fi
done
