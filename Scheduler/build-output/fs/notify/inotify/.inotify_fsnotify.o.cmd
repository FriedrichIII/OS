cmd_fs/notify/inotify/inotify_fsnotify.o := gcc -Wp,-MD,fs/notify/inotify/.inotify_fsnotify.o.d  -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/4.7/include -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include -Iarch/um/include/generated  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include -Iinclude -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/uapi -Iarch/um/include/generated/uapi -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi -Iinclude/generated/uapi -include /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kconfig.h  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/fs/notify/inotify -Ifs/notify/inotify -D__KERNEL__ -m64   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/generated -Iarch/x86/include/generated  -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/generated/uapi -Iarch/x86/include/generated/uapi -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -mcmodel=large -fno-builtin -m64 -funit-at-a-time -D__arch_um__   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared   -I/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas -Dvmap=kernel_vmap -Din6addr_loopback=kernel_in6addr_loopback -Din6addr_any=kernel_in6addr_any -Dstrrchr=kernel_strrchr -D_LARGEFILE64_SOURCE -Derrno=kernel_errno -Dsigprocmask=kernel_sigprocmask -Dmktime=kernel_mktime -Wframe-larger-than=1024 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(inotify_fsnotify)"  -D"KBUILD_MODNAME=KBUILD_STR(inotify_fsnotify)" -c -o fs/notify/inotify/inotify_fsnotify.o /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/fs/notify/inotify/inotify_fsnotify.c

source_fs/notify/inotify/inotify_fsnotify.o := /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/fs/notify/inotify/inotify_fsnotify.c

deps_fs/notify/inotify/inotify_fsnotify.o := \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/dcache.h \
    $(wildcard include/config/64bit.h) \
    $(wildcard include/config/smp.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/atomic.h \
    $(wildcard include/config/x86/64.h) \
    $(wildcard include/config/x86/32.h) \
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
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
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
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/posix_types.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/posix_types_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/posix_types.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/asm/processor.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/faultinfo.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/faultinfo_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/asm/processor_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/user.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/user_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/asm/page.h \
    $(wildcard include/config/3/level/pgtables.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/const.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/asm/vm-flags.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/mem.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/getorder.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/bitops.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/bitops.h \
    $(wildcard include/config/x86/cmov.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/alternative.h \
    $(wildcard include/config/paravirt.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/stringify.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/asm.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/cpufeature.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/asm/required-features.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/bitops/sched.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/asm/arch_hweight.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/bitops/arch_hweight.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/bitops/const_hweight.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/bitops/le.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/byteorder.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/byteorder/little_endian.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/byteorder/little_endian.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/swab.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/swab.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/swab.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/byteorder/generic.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/bitops/ext2-atomic-setbit.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/asm/processor-generic.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/asm/ptrace.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/asm/ptrace-generic.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/ptrace-abi.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/ptrace.h \
  include/generated/user_constants.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/ptrace_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/errno.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/errno.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/errno-base.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/registers.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/archsetjmp.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared/sysdep/archsetjmp_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/prefetch.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/asm/cache.h \
    $(wildcard include/config/uml/x86.h) \
    $(wildcard include/config/x86/l1/cache/shift.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/cmpxchg.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/cmpxchg_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/atomic64_64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/atomic-long.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/rculist.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/rcupdate.h \
    $(wildcard include/config/rcu/torture/test.h) \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/rcu/user/qs.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/tiny/preempt/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/prove/rcu.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/preempt/rt.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/symbol/prefix.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /usr/lib/gcc/x86_64-linux-gnu/4.7/include/stdarg.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/linkage.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/linkage.h \
    $(wildcard include/config/x86/alignment/16.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/typecheck.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/printk.h \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
    $(wildcard include/config/modules.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kern_levels.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/dynamic_debug.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/string.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/string.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/string_64.h \
    $(wildcard include/config/kmemcheck.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/errno.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/errno.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/kernel.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/sysinfo.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
    $(wildcard include/config/debug/stack/usage.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
  arch/um/include/generated/asm/bug.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/asm/thread_info.h \
    $(wildcard include/config/kernel/stack/order.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/asm/uaccess.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/asm/elf.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas/skas.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/asm/irqflags.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/bottom_half.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/asm/barrier.h \
    $(wildcard include/config/x86/ppro/fence.h) \
    $(wildcard include/config/x86/oostore.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/asm/segment.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/nops.h \
    $(wildcard include/config/mk7.h) \
    $(wildcard include/config/x86/p6/nop.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/spinlock_types.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/spinlock_types_up.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/rwlock_types.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/spinlock_up.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/rwlock.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/spinlock_api_up.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/bitmap.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/seqlock.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/completion.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/wait.h \
  arch/um/include/generated/asm/current.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/current.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/wait.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/rcutiny.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/rculist_bl.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/list_bl.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/bit_spinlock.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/fs.h \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kdev_t.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/kdev_t.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/path.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/stat.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/stat.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/stat.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/math64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/div64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/div64.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/time.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/uidgid.h \
    $(wildcard include/config/uidgid/strict/type/checks.h) \
    $(wildcard include/config/user/ns.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/highuid.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/radix-tree.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/rbtree.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/pid.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/capability.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/capability.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/semaphore.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/fiemap.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/shrinker.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/migrate_mode.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/percpu-rwsem.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/rwsem.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/pfn.h \
  arch/um/include/generated/asm/percpu.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/percpu.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/blk_types.h \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/blk/dev/integrity.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/fs.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/limits.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/ioctl.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/ioctl.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/ioctl.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/ioctl.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/percpu_counter.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/dqblk_xfs.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/dqblk_v1.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/dqblk_v2.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/dqblk_qtree.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/projid.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/quota.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/nfs_fs_i.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/fcntl.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/fcntl.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/fcntl.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/fcntl.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/err.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/fsnotify_backend.h \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/fanotify/access/permissions.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/idr.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/inotify.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/sysctl.h \
    $(wildcard include/config/sysctl.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/sysctl.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/inotify.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/debug/slab.h) \
    $(wildcard include/config/slab.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/gfp.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/cma.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/compaction.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/have/arch/pfn/valid.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/nodemask.h \
    $(wildcard include/config/movable/node.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/generated/bounds.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/notifier.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/srcu.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/jiffies.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/timex.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/timex.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/param.h \
  arch/um/include/generated/asm/param.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/param.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/asm/timex.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
  arch/um/include/generated/asm/topology.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/topology.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/slab_def.h \
    $(wildcard include/config/memcg/kmem.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kmalloc_sizes.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/no/hz.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/have/hw/breakpoint.h) \
    $(wildcard include/config/uprobes.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/cfs/bandwidth.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/mm/owner.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/sched.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/have/cmpxchg/double.h) \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/transparent/hugepage.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/auxvec.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/auxvec.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/auxvec.h \
    $(wildcard include/config/ia32/emulation.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/guard.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/uprobes.h \
    $(wildcard include/config/arch/supports/uprobes.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/asm/mmu.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas/mm_id.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/asm/mm_context.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/ldt.h \
  arch/um/include/generated/asm/cputime.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/cputime.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/sem.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/sem.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/ipc.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/ipc.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/ipcbuf.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/ipcbuf.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/sembuf.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/signal.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/signal.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/signal.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/signal.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/signal-defs.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/asm/sigcontext.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/sigcontext.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/siginfo.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/siginfo.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/siginfo.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/proportions.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
    $(wildcard include/config/seccomp/filter.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/seccomp.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/resource.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/resource.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi/asm/resource.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/asm-generic/resource.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/asm-generic/resource.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/timerqueue.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/latencytop.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/key.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/aio.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/aio_abi.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/uio.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi/linux/uio.h \
  /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/fs/notify/inotify/inotify.h \

fs/notify/inotify/inotify_fsnotify.o: $(deps_fs/notify/inotify/inotify_fsnotify.o)

$(deps_fs/notify/inotify/inotify_fsnotify.o):
