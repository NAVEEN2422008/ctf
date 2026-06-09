#!/bin/bash

gcc vm.c -o vm \
-fPIE -pie \
-fno-stack-protector \
-Wl,-z,relro,-z,now \
-s

chmod +x vm

echo "Built!"
