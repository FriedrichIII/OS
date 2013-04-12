#!/bin/sh
cat <<HD
***** prio ******
HD
cd test2/
cat README
cat <<HD
*****************
* Our Scheduler *
*****************
HD
./prio.sh
cd ..
cat <<HD
****** End ******
HD
