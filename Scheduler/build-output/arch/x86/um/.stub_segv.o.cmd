cmd_arch/x86/um/stub_segv.o := gcc -Wp,-MD,arch/x86/um/.stub_segv.o.d 	 -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -mcmodel=large -fno-builtin -m64 -funit-at-a-time -D__arch_um__ -Dvmap=kernel_vmap -Din6addr_loopback=kernel_in6addr_loopback -Din6addr_any=kernel_in6addr_any -Dstrrchr=kernel_strrchr -D_LARGEFILE64_SOURCE  -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas  -D_FILE_OFFSET_BITS=64 -idirafter include -D_GNU_SOURCE -D_LARGEFILE64_SOURCE  -fno-PIC  -fno-pic  -fno-stack-protector  -c -o arch/x86/um/stub_segv.o /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/stub_segv.c

source_arch/x86/um/stub_segv.o := /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/stub_segv.c

deps_arch/x86/um/stub_segv.o := \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/stub.h \
  /usr/include/x86_64-linux-gnu/asm/unistd.h \
  /usr/include/x86_64-linux-gnu/asm/unistd_64.h \
  /usr/include/x86_64-linux-gnu/sys/mman.h \
  /usr/include/features.h \
  /usr/include/x86_64-linux-gnu/bits/predefs.h \
  /usr/include/x86_64-linux-gnu/sys/cdefs.h \
  /usr/include/x86_64-linux-gnu/bits/wordsize.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
  /usr/include/x86_64-linux-gnu/bits/types.h \
  /usr/include/x86_64-linux-gnu/bits/typesizes.h \
  /usr/lib/gcc/x86_64-linux-gnu/4.7/include/stddef.h \
  /usr/include/x86_64-linux-gnu/bits/mman.h \
  /usr/include/signal.h \
  /usr/include/x86_64-linux-gnu/bits/sigset.h \
  /usr/include/x86_64-linux-gnu/bits/signum.h \
  /usr/include/time.h \
  /usr/include/x86_64-linux-gnu/bits/siginfo.h \
  /usr/include/x86_64-linux-gnu/bits/sigaction.h \
  /usr/include/x86_64-linux-gnu/bits/sigcontext.h \
  /usr/include/x86_64-linux-gnu/bits/sigstack.h \
  /usr/include/x86_64-linux-gnu/sys/ucontext.h \
  /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h \
  /usr/include/x86_64-linux-gnu/bits/sigthread.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/as-layout.h \
  include/generated/asm-offsets.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/uml/x86.h) \
    $(wildcard include/config/64bit.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/ptrace.h \
  include/generated/user_constants.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/faultinfo.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/faultinfo_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/ptrace_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas/stub-data.h \
  /usr/include/x86_64-linux-gnu/sys/time.h \
  /usr/include/x86_64-linux-gnu/bits/time.h \
  /usr/include/x86_64-linux-gnu/sys/select.h \
  /usr/include/x86_64-linux-gnu/bits/select.h \
  /usr/include/x86_64-linux-gnu/bits/select2.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/stub_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/ptrace_user.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/mcontext.h \

arch/x86/um/stub_segv.o: $(deps_arch/x86/um/stub_segv.o)

$(deps_arch/x86/um/stub_segv.o):
