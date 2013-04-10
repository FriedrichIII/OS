cmd_arch/x86/um/stub_64.o := gcc -Wp,-MD,arch/x86/um/.stub_64.o.d  -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include -Iarch/um/include/generated  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include -Iinclude -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/uapi -Iarch/um/include/generated/uapi -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi -Iinclude/generated/uapi -include /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kconfig.h -D__KERNEL__ -m64   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/generated -Iarch/x86/include/generated  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/generated/uapi -Iarch/x86/include/generated/uapi -D__ASSEMBLY__ -m64   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared -gdwarf-2   -c -o arch/x86/um/stub_64.o /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/stub_64.S

source_arch/x86/um/stub_64.o := /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/stub_64.S

deps_arch/x86/um/stub_64.o := \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/as-layout.h \
  include/generated/asm-offsets.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/uml/x86.h) \
    $(wildcard include/config/64bit.h) \

arch/x86/um/stub_64.o: $(deps_arch/x86/um/stub_64.o)

$(deps_arch/x86/um/stub_64.o):
