cmd_lib/decompress.o := gcc -Wp,-MD,lib/.decompress.o.d  -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include -Iarch/um/include/generated  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include -Iinclude -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/uapi -Iarch/um/include/generated/uapi -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi -Iinclude/generated/uapi -include /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kconfig.h  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/lib -Ilib -D__KERNEL__ -m64   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/generated -Iarch/x86/include/generated  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/generated/uapi -Iarch/x86/include/generated/uapi -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -mcmodel=large -fno-builtin -m64 -funit-at-a-time -D__arch_um__   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas -Dvmap=kernel_vmap -Din6addr_loopback=kernel_in6addr_loopback -Din6addr_any=kernel_in6addr_any -Dstrrchr=kernel_strrchr -D_LARGEFILE64_SOURCE -Derrno=kernel_errno -Dsigprocmask=kernel_sigprocmask -Dmktime=kernel_mktime -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(decompress)"  -D"KBUILD_MODNAME=KBUILD_STR(decompress)" -c -o lib/decompress.o /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/lib/decompress.c

source_lib/decompress.o := /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/lib/decompress.c

deps_lib/decompress.o := \
    $(wildcard include/config/decompress/gzip.h) \
    $(wildcard include/config/decompress/bzip2.h) \
    $(wildcard include/config/decompress/lzma.h) \
    $(wildcard include/config/decompress/xz.h) \
    $(wildcard include/config/decompress/lzo.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/decompress/generic.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/decompress/bunzip2.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/decompress/unlzma.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/decompress/unxz.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/decompress/inflate.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/decompress/unlzo.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/types.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/types.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/types.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/int-ll64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/int-ll64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/bitsperlong.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/bitsperlong.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/bitsperlong.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/posix_types.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/stddef.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/stddef.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/compiler-gcc4.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/posix_types.h \
    $(wildcard include/config/x86/32.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/posix_types_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/posix_types.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /usr/lib/gcc/x86_64-linux-gnu/4.7/include/stdarg.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/string.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/string.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/string_64.h \
    $(wildcard include/config/kmemcheck.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
    $(wildcard include/config/modules.h) \

lib/decompress.o: $(deps_lib/decompress.o)

$(deps_lib/decompress.o):
