cmd_arch/um/os-Linux/aio.o := gcc -Wp,-MD,arch/um/os-Linux/.aio.o.d  -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -mcmodel=large -fno-builtin -m64 -funit-at-a-time -D__arch_um__ -Dvmap=kernel_vmap -Din6addr_loopback=kernel_in6addr_loopback -Din6addr_any=kernel_in6addr_any -Dstrrchr=kernel_strrchr -D_LARGEFILE64_SOURCE  -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas  -D_FILE_OFFSET_BITS=64 -idirafter include -D_GNU_SOURCE -D_LARGEFILE64_SOURCE -include /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kern_levels.h -include user.h -DHAVE_AIO_ABI -c -o arch/um/os-Linux/aio.o /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/os-Linux/aio.c

source_arch/um/os-Linux/aio.o := /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/os-Linux/aio.c

deps_arch/um/os-Linux/aio.o := \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kern_levels.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/user.h \
    $(wildcard include/config/printk.h) \
  include/generated/asm-offsets.h \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/uml/x86.h) \
    $(wildcard include/config/64bit.h) \
  /usr/lib/gcc/x86_64-linux-gnu/4.7/include/stddef.h \
  /usr/include/unistd.h \
  /usr/include/features.h \
  /usr/include/x86_64-linux-gnu/bits/predefs.h \
  /usr/include/x86_64-linux-gnu/sys/cdefs.h \
  /usr/include/x86_64-linux-gnu/bits/wordsize.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
  /usr/include/x86_64-linux-gnu/bits/posix_opt.h \
  /usr/include/x86_64-linux-gnu/bits/environments.h \
  /usr/include/x86_64-linux-gnu/bits/types.h \
  /usr/include/x86_64-linux-gnu/bits/typesizes.h \
  /usr/include/x86_64-linux-gnu/bits/confname.h \
  /usr/include/getopt.h \
  /usr/include/x86_64-linux-gnu/bits/unistd.h \
  /usr/include/sched.h \
  /usr/include/time.h \
  /usr/include/x86_64-linux-gnu/bits/sched.h \
  /usr/include/signal.h \
  /usr/include/x86_64-linux-gnu/bits/sigset.h \
  /usr/include/x86_64-linux-gnu/bits/signum.h \
  /usr/include/x86_64-linux-gnu/bits/siginfo.h \
  /usr/include/x86_64-linux-gnu/bits/sigaction.h \
  /usr/include/x86_64-linux-gnu/bits/sigcontext.h \
  /usr/include/x86_64-linux-gnu/bits/sigstack.h \
  /usr/include/x86_64-linux-gnu/sys/ucontext.h \
  /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
  /usr/include/x86_64-linux-gnu/bits/sigthread.h \
  /usr/include/errno.h \
  /usr/include/x86_64-linux-gnu/bits/errno.h \
  /usr/include/linux/errno.h \
  /usr/include/x86_64-linux-gnu/asm/errno.h \
  /usr/include/asm-generic/errno.h \
  /usr/include/asm-generic/errno-base.h \
  /usr/include/x86_64-linux-gnu/sys/time.h \
  /usr/include/x86_64-linux-gnu/bits/time.h \
  /usr/include/x86_64-linux-gnu/sys/select.h \
  /usr/include/x86_64-linux-gnu/bits/select.h \
  /usr/include/x86_64-linux-gnu/bits/select2.h \
  /usr/include/x86_64-linux-gnu/asm/unistd.h \
  /usr/include/x86_64-linux-gnu/asm/unistd_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/aio.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/init.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/kern_util.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/ptrace.h \
  include/generated/user_constants.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/faultinfo.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/faultinfo_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/ptrace_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/os.h \
  /usr/lib/gcc/x86_64-linux-gnu/4.7/include/stdarg.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/irq_user.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/longjmp.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/archsetjmp.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/archsetjmp_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas/mm_id.h \
  /usr/include/linux/aio_abi.h \
  /usr/include/linux/types.h \
  /usr/include/x86_64-linux-gnu/asm/types.h \
  /usr/include/asm-generic/types.h \
  /usr/include/asm-generic/int-ll64.h \
  /usr/include/x86_64-linux-gnu/asm/bitsperlong.h \
  /usr/include/asm-generic/bitsperlong.h \
  /usr/include/linux/posix_types.h \
  /usr/include/linux/stddef.h \
  /usr/include/x86_64-linux-gnu/asm/posix_types.h \
  /usr/include/x86_64-linux-gnu/asm/posix_types_64.h \
  /usr/include/asm-generic/posix_types.h \
  /usr/include/x86_64-linux-gnu/asm/byteorder.h \
  /usr/include/linux/byteorder/little_endian.h \
  /usr/include/linux/swab.h \
  /usr/include/x86_64-linux-gnu/asm/swab.h \
    $(wildcard include/config/x86/bswap.h) \

arch/um/os-Linux/aio.o: $(deps_arch/um/os-Linux/aio.o)

$(deps_arch/um/os-Linux/aio.o):
