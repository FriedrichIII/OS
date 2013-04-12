#!/bin/sh
cat <<HD
***** preem *****
HD
cd test5/
cat README
cat <<HD
*****************
* Our Scheduler *
*****************
HD
./preem.sh
cd ..
cat <<HD
****** End ******
HD
