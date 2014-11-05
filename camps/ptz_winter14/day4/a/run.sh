#!/bin/bash

for((i=0;i<100;++i)); do
    perl gen.pl 3000 > input.txt
    if ! ./a; then 
        echo FAIL
        break
    fi
done
