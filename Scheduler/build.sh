#!/bin/sh
cd linux-3.8.3
make ARCH=um O=../build-output
cd ..
