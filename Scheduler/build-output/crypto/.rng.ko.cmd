cmd_crypto/rng.ko := ld -r  -m elf_x86_64 -T /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/scripts/module-common.lds --build-id  -o crypto/rng.ko crypto/rng.o crypto/rng.mod.o
