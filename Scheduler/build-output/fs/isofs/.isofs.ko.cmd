cmd_fs/isofs/isofs.ko := ld -r  -m elf_x86_64 -T /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/scripts/module-common.lds --build-id  -o fs/isofs/isofs.ko fs/isofs/isofs.o fs/isofs/isofs.mod.o
