#!/bin/bash

for i in `seq -w 1 10`; do
    tail -n +2 res$i.out > pap$i.out
done
rm -f res.zip
zip res.zip pap??.out
