cmd_arch/um/drivers/null.o := gcc -Wp,-MD,arch/um/drivers/.null.o.d  -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -mcmodel=large -fno-builtin -m64 -funit-at-a-time -D__arch_um__ -Dvmap=kernel_vmap -Din6addr_loopback=kernel_in6addr_loopback -Din6addr_any=kernel_in6addr_any -Dstrrchr=kernel_strrchr -D_LARGEFILE64_SOURCE  -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas  -D_FILE_OFFSET_BITS=64 -idirafter include -D_GNU_SOURCE -D_LARGEFILE64_SOURCE -include /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kern_levels.h -include user.h -DDEV_NULL=\"/dev/null\" -c -o arch/um/drivers/null.o /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/drivers/null.c

source_arch/um/drivers/null.o := /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/drivers/null.c

deps_arch/um/drivers/null.o := \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kern_levels.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/user.h \
    $(wildcard include/config/printk.h) \
  include/generated/asm-offsets.h \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/uml/x86.h) \
    $(wildcard include/config/64bit.h) \
  /usr/lib/gcc/x86_64-linux-gnu/4.7/include/stddef.h \
  /usr/include/errno.h \
  /usr/include/features.h \
  /usr/include/x86_64-linux-gnu/bits/predefs.h \
  /usr/include/x86_64-linux-gnu/sys/cdefs.h \
  /usr/include/x86_64-linux-gnu/bits/wordsize.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
  /usr/include/x86_64-linux-gnu/bits/errno.h \
  /usr/include/linux/errno.h \
  /usr/include/x86_64-linux-gnu/asm/errno.h \
  /usr/include/asm-generic/errno.h \
  /usr/include/asm-generic/errno-base.h \
  /usr/include/fcntl.h \
  /usr/include/x86_64-linux-gnu/bits/fcntl.h \
  /usr/include/x86_64-linux-gnu/sys/types.h \
  /usr/include/x86_64-linux-gnu/bits/types.h \
  /usr/include/x86_64-linux-gnu/bits/typesizes.h \
  /usr/include/time.h \
  /usr/include/endian.h \
  /usr/include/x86_64-linux-gnu/bits/endian.h \
  /usr/include/x86_64-linux-gnu/bits/byteswap.h \
  /usr/include/x86_64-linux-gnu/sys/select.h \
  /usr/include/x86_64-linux-gnu/bits/select.h \
  /usr/include/x86_64-linux-gnu/bits/sigset.h \
  /usr/include/x86_64-linux-gnu/bits/time.h \
  /usr/include/x86_64-linux-gnu/bits/select2.h \
  /usr/include/x86_64-linux-gnu/sys/sysmacros.h \
  /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
  /usr/include/x86_64-linux-gnu/bits/uio.h \
  /usr/include/x86_64-linux-gnu/bits/stat.h \
  /usr/include/x86_64-linux-gnu/bits/fcntl2.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/drivers/chan_user.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/init.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/os.h \
  /usr/lib/gcc/x86_64-linux-gnu/4.7/include/stdarg.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/irq_user.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/ptrace.h \
  include/generated/user_constants.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/faultinfo.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/faultinfo_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/ptrace_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/longjmp.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/archsetjmp.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/archsetjmp_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas/mm_id.h \

arch/um/drivers/null.o: $(deps_arch/um/drivers/null.o)

$(deps_arch/um/drivers/null.o):