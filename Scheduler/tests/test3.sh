#!/bin/sh
cat <<HD
***** yield *****
HD
cd test3/
cat README
cat <<HD
*****************
* Our Scheduler *
*****************
HD
./yield.sh
cd ..
cat <<HD
****** End ******
HD
