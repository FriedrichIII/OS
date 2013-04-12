#!/bin/sh
cat <<HD
****** rr *******
HD
cd test1/
cat README
cat <<HD
*****************
* Our Scheduler *
*****************
HD
./rr.sh
cd ..
cat <<HD
****** End ******
HD
