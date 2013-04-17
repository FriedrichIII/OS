#!/bin/sh

echo 3 > /proc/sys/kernel/sched_dummy_timeslice
echo 7 > /proc/sys/kernel/sched_dummy_age_threshold

./test6
