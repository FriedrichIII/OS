cmd_crypto/krng.ko := ld -r  -m elf_x86_64 -T /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/scripts/module-common.lds --build-id  -o crypto/krng.ko crypto/krng.o crypto/krng.mod.o
