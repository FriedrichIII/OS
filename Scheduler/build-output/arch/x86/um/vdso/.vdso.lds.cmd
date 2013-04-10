cmd_arch/x86/um/vdso/vdso.lds := gcc -E -Wp,-MD,arch/x86/um/vdso/.vdso.lds.d  -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include -Iarch/um/include/generated  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include -Iinclude -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/uapi -Iarch/um/include/generated/uapi -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi -Iinclude/generated/uapi -include /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kconfig.h -D__KERNEL__ -m64   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/generated -Iarch/x86/include/generated  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/generated/uapi -Iarch/x86/include/generated/uapi -P -C -P -C -Uum -D__ASSEMBLY__ -DLINKER_SCRIPT -o arch/x86/um/vdso/vdso.lds /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/vdso/vdso.lds.S

source_arch/x86/um/vdso/vdso.lds := /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/vdso/vdso.lds.S

deps_arch/x86/um/vdso/vdso.lds := \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/vdso/vdso-layout.lds.S \

arch/x86/um/vdso/vdso.lds: $(deps_arch/x86/um/vdso/vdso.lds)

$(deps_arch/x86/um/vdso/vdso.lds):
