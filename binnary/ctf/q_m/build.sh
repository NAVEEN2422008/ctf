#!/bin/bash

gcc chall.c -o chall \
-O2 \
-fno-stack-protector \
-fomit-frame-pointer \
-no-pie \
-s

chmod +x chall

echo "Built!"
