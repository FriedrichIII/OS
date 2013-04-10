cmd_arch/um/kernel/config.tmp := sed -e 's/"/\\"/g' -e 's/^/"/' -e 's/$$/\\n",/' /home/valerian/Documents/ba6/OS/repo/Scheduler/build-output/.config > arch/um/kernel/config.tmp
