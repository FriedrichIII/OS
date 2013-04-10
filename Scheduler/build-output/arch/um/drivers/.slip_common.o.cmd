cmd_arch/um/drivers/slip_common.o := gcc -Wp,-MD,arch/um/drivers/.slip_common.o.d  -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -mcmodel=large -fno-builtin -m64 -funit-at-a-time -D__arch_um__ -Dvmap=kernel_vmap -Din6addr_loopback=kernel_in6addr_loopback -Din6addr_any=kernel_in6addr_any -Dstrrchr=kernel_strrchr -D_LARGEFILE64_SOURCE  -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas  -D_FILE_OFFSET_BITS=64 -idirafter include -D_GNU_SOURCE -D_LARGEFILE64_SOURCE -include /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kern_levels.h -include user.h  -c -o arch/um/drivers/slip_common.o /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/drivers/slip_common.c

source_arch/um/drivers/slip_common.o := /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/drivers/slip_common.c

deps_arch/um/drivers/slip_common.o := \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kern_levels.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/user.h \
    $(wildcard include/config/printk.h) \
  include/generated/asm-offsets.h \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/uml/x86.h) \
    $(wildcard include/config/64bit.h) \
  /usr/lib/gcc/x86_64-linux-gnu/4.7/include/stddef.h \
  /usr/include/string.h \
  /usr/include/features.h \
  /usr/include/x86_64-linux-gnu/bits/predefs.h \
  /usr/include/x86_64-linux-gnu/sys/cdefs.h \
  /usr/include/x86_64-linux-gnu/bits/wordsize.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs.h \
  /usr/include/x86_64-linux-gnu/gnu/stubs-64.h \
  /usr/include/xlocale.h \
  /usr/include/x86_64-linux-gnu/bits/string3.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/drivers/slip_common.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/net_user.h \

arch/um/drivers/slip_common.o: $(deps_arch/um/drivers/slip_common.o)

$(deps_arch/um/drivers/slip_common.o):
