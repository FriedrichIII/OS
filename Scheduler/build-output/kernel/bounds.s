	.file	"bounds.c"
# GNU C (Ubuntu/Linaro 4.7.2-2ubuntu1) version 4.7.2 (x86_64-linux-gnu)
#	compiled by GNU C version 4.7.2, GMP version 5.0.2, MPFR version 3.1.0-p3, MPC version 0.9
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passées:  -nostdinc
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include
# -I arch/um/include/generated
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include
# -I include
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/uapi
# -I arch/um/include/generated/uapi
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/uapi
# -I include/generated/uapi
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/. -I .
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/uapi
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/generated
# -I arch/x86/include/generated
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/include/generated/uapi
# -I arch/x86/include/generated/uapi
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas
# -imultiarch x86_64-linux-gnu -D __KERNEL__ -D __arch_um__
# -D vmap=kernel_vmap -D in6addr_loopback=kernel_in6addr_loopback
# -D in6addr_any=kernel_in6addr_any -D strrchr=kernel_strrchr
# -D _LARGEFILE64_SOURCE -D errno=kernel_errno
# -D sigprocmask=kernel_sigprocmask -D mktime=kernel_mktime
# -D CC_HAVE_ASM_GOTO -D KBUILD_STR(s)=#s
# -D KBUILD_BASENAME=KBUILD_STR(bounds)
# -D KBUILD_MODNAME=KBUILD_STR(bounds)
# -isystem /usr/lib/gcc/x86_64-linux-gnu/4.7/include
# -include /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kconfig.h
# -MD kernel/.bounds.s.d
# /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/kernel/bounds.c
# -mcmodel=large -m64 -mtune=generic -march=x86-64
# -auxbase-strip kernel/bounds.s -g -Os -Wall -Wundef -Wstrict-prototypes
# -Wno-trigraphs -Werror=implicit-function-declaration -Wno-format-security
# -Wframe-larger-than=1024 -Wno-unused-but-set-variable
# -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-aliasing
# -fno-common -fno-delete-null-pointer-checks -fno-builtin -funit-at-a-time
# -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls
# -fno-strict-overflow -fconserve-stack -fverbose-asm
# options autorisées:  -fasynchronous-unwind-tables -fauto-inc-dec
# -fbranch-count-reg -fcaller-saves -fcombine-stack-adjustments
# -fcompare-elim -fcprop-registers -fcrossjumping -fcse-follow-jumps
# -fdebug-types-section -fdefer-pop -fdevirtualize -fdwarf2-cfi-asm
# -fearly-inlining -feliminate-unused-debug-types -fexpensive-optimizations
# -fforward-propagate -ffunction-cse -fgcse -fgcse-lm -fgnu-runtime
# -fguess-branch-probability -fident -fif-conversion -fif-conversion2
# -findirect-inlining -finline -finline-atomics -finline-functions
# -finline-functions-called-once -finline-small-functions -fipa-cp
# -fipa-profile -fipa-pure-const -fipa-reference -fipa-sra
# -fira-share-save-slots -fira-share-spill-slots -fivopts
# -fkeep-static-consts -fleading-underscore -fmath-errno -fmerge-constants
# -fmerge-debug-strings -fmove-loop-invariants -foptimize-register-move
# -fpartial-inlining -fpeephole -fpeephole2 -fprefetch-loop-arrays -free
# -freg-struct-return -fregmove -freorder-blocks -freorder-functions
# -frerun-cse-after-loop -fsched-critical-path-heuristic
# -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
# -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
# -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-insns2
# -fshow-column -fshrink-wrap -fsigned-zeros -fsplit-ivs-in-unroller
# -fsplit-wide-types -fstrict-volatile-bitfields -fthread-jumps
# -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp -ftree-builtin-call-dce
# -ftree-ccp -ftree-ch -ftree-copy-prop -ftree-copyrename -ftree-cselim
# -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
# -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop -ftree-pre
# -ftree-pta -ftree-reassoc -ftree-scev-cprop -ftree-sink
# -ftree-slp-vectorize -ftree-sra -ftree-switch-conversion
# -ftree-tail-merge -ftree-ter -ftree-vect-loop-version -ftree-vrp
# -funit-at-a-time -funwind-tables -fvar-tracking
# -fvar-tracking-assignments -fvect-cost-model -fverbose-asm
# -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
# -malign-stringops -mfancy-math-387 -mfp-ret-in-387 -mglibc -mieee-fp
# -mmmx -mno-sse4 -mpush-args -mred-zone -msse -msse2 -mtls-direct-seg-refs

	.text
.Ltext0:
	.globl	foo
	.type	foo, @function
foo:
.LFB137:
	.file 1 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/kernel/bounds.c"
	.loc 1 15 0
	.cfi_startproc
	pushq	%rbp	#
.LCFI0:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
.LCFI1:
	.cfi_def_cfa_register 6
	.loc 1 17 0
#APP
# 17 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/kernel/bounds.c" 1
	
->NR_PAGEFLAGS $22 __NR_PAGEFLAGS	#
# 0 "" 2
	.loc 1 18 0
# 18 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/kernel/bounds.c" 1
	
->MAX_NR_ZONES $2 __MAX_NR_ZONES	#
# 0 "" 2
	.loc 1 19 0
# 19 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/kernel/bounds.c" 1
	
->NR_PCG_FLAGS $3 __NR_PCG_FLAGS	#
# 0 "" 2
	.loc 1 21 0
#NO_APP
	popq	%rbp	#
.LCFI2:
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE137:
	.size	foo, .-foo
.Letext0:
	.file 2 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/page-flags.h"
	.file 3 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/mmzone.h"
	.file 4 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/printk.h"
	.file 5 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/kernel.h"
	.file 6 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/include/linux/page_cgroup.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x1cf
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF51
	.byte	0x1
	.long	.LASF52
	.long	.LASF53
	.quad	.Ltext0
	.quad	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF3
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF4
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF8
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF10
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.long	.LASF11
	.uleb128 0x4
	.long	.LASF40
	.byte	0x4
	.byte	0x2
	.byte	0x4a
	.long	0x13d
	.uleb128 0x5
	.long	.LASF12
	.sleb128 0
	.uleb128 0x5
	.long	.LASF13
	.sleb128 1
	.uleb128 0x5
	.long	.LASF14
	.sleb128 2
	.uleb128 0x5
	.long	.LASF15
	.sleb128 3
	.uleb128 0x5
	.long	.LASF16
	.sleb128 4
	.uleb128 0x5
	.long	.LASF17
	.sleb128 5
	.uleb128 0x5
	.long	.LASF18
	.sleb128 6
	.uleb128 0x5
	.long	.LASF19
	.sleb128 7
	.uleb128 0x5
	.long	.LASF20
	.sleb128 8
	.uleb128 0x5
	.long	.LASF21
	.sleb128 9
	.uleb128 0x5
	.long	.LASF22
	.sleb128 10
	.uleb128 0x5
	.long	.LASF23
	.sleb128 11
	.uleb128 0x5
	.long	.LASF24
	.sleb128 12
	.uleb128 0x5
	.long	.LASF25
	.sleb128 13
	.uleb128 0x5
	.long	.LASF26
	.sleb128 14
	.uleb128 0x5
	.long	.LASF27
	.sleb128 15
	.uleb128 0x5
	.long	.LASF28
	.sleb128 16
	.uleb128 0x5
	.long	.LASF29
	.sleb128 17
	.uleb128 0x5
	.long	.LASF30
	.sleb128 18
	.uleb128 0x5
	.long	.LASF31
	.sleb128 19
	.uleb128 0x5
	.long	.LASF32
	.sleb128 20
	.uleb128 0x5
	.long	.LASF33
	.sleb128 21
	.uleb128 0x5
	.long	.LASF34
	.sleb128 22
	.uleb128 0x5
	.long	.LASF35
	.sleb128 8
	.uleb128 0x5
	.long	.LASF36
	.sleb128 12
	.uleb128 0x5
	.long	.LASF37
	.sleb128 8
	.uleb128 0x5
	.long	.LASF38
	.sleb128 4
	.uleb128 0x5
	.long	.LASF39
	.sleb128 11
	.byte	0
	.uleb128 0x6
	.long	.LASF41
	.byte	0x4
	.byte	0x3
	.value	0x102
	.long	0x15d
	.uleb128 0x5
	.long	.LASF42
	.sleb128 0
	.uleb128 0x5
	.long	.LASF43
	.sleb128 1
	.uleb128 0x5
	.long	.LASF44
	.sleb128 2
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.byte	0x6
	.byte	0x4
	.long	0x17e
	.uleb128 0x5
	.long	.LASF45
	.sleb128 0
	.uleb128 0x5
	.long	.LASF46
	.sleb128 1
	.uleb128 0x5
	.long	.LASF47
	.sleb128 2
	.uleb128 0x5
	.long	.LASF48
	.sleb128 3
	.byte	0
	.uleb128 0x8
	.byte	0x1
	.string	"foo"
	.byte	0x1
	.byte	0xe
	.byte	0x1
	.quad	.LFB137
	.quad	.LFE137
	.long	.LLST0
	.byte	0x1
	.uleb128 0x9
	.long	0x49
	.long	0x1a7
	.uleb128 0xa
	.byte	0
	.uleb128 0xb
	.long	.LASF49
	.byte	0x4
	.byte	0x22
	.long	0x19c
	.byte	0x1
	.byte	0x1
	.uleb128 0x9
	.long	0x73
	.long	0x1bf
	.uleb128 0xa
	.byte	0
	.uleb128 0xc
	.long	.LASF50
	.byte	0x5
	.value	0x1af
	.long	0x1cd
	.byte	0x1
	.byte	0x1
	.uleb128 0xd
	.long	0x1b4
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.quad	.LFB137-.Ltext0
	.quad	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	.LCFI0-.Ltext0
	.quad	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 16
	.quad	.LCFI1-.Ltext0
	.quad	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x76
	.sleb128 16
	.quad	.LCFI2-.Ltext0
	.quad	.LFE137-.Ltext0
	.value	0x2
	.byte	0x77
	.sleb128 8
	.quad	0
	.quad	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF47:
	.string	"PCG_MIGRATION"
.LASF26:
	.string	"PG_head"
.LASF49:
	.string	"console_printk"
.LASF22:
	.string	"PG_reserved"
.LASF42:
	.string	"ZONE_NORMAL"
.LASF29:
	.string	"PG_mappedtodisk"
.LASF12:
	.string	"PG_locked"
.LASF16:
	.string	"PG_dirty"
.LASF25:
	.string	"PG_writeback"
.LASF23:
	.string	"PG_private"
.LASF34:
	.string	"__NR_PAGEFLAGS"
.LASF44:
	.string	"__MAX_NR_ZONES"
.LASF36:
	.string	"PG_fscache"
.LASF14:
	.string	"PG_referenced"
.LASF28:
	.string	"PG_swapcache"
.LASF41:
	.string	"zone_type"
.LASF7:
	.string	"long unsigned int"
.LASF3:
	.string	"short unsigned int"
.LASF31:
	.string	"PG_swapbacked"
.LASF35:
	.string	"PG_checked"
.LASF1:
	.string	"unsigned char"
.LASF17:
	.string	"PG_lru"
.LASF27:
	.string	"PG_tail"
.LASF40:
	.string	"pageflags"
.LASF45:
	.string	"PCG_LOCK"
.LASF4:
	.string	"unsigned int"
.LASF13:
	.string	"PG_error"
.LASF6:
	.string	"long long unsigned int"
.LASF37:
	.string	"PG_pinned"
.LASF19:
	.string	"PG_slab"
.LASF52:
	.string	"/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/kernel/bounds.c"
.LASF20:
	.string	"PG_owner_priv_1"
.LASF18:
	.string	"PG_active"
.LASF8:
	.string	"sizetype"
.LASF24:
	.string	"PG_private_2"
.LASF5:
	.string	"long long int"
.LASF9:
	.string	"char"
.LASF32:
	.string	"PG_unevictable"
.LASF38:
	.string	"PG_savepinned"
.LASF51:
	.string	"GNU C 4.7.2"
.LASF2:
	.string	"short int"
.LASF50:
	.string	"hex_asc"
.LASF46:
	.string	"PCG_USED"
.LASF21:
	.string	"PG_arch_1"
.LASF10:
	.string	"long int"
.LASF43:
	.string	"ZONE_MOVABLE"
.LASF15:
	.string	"PG_uptodate"
.LASF48:
	.string	"__NR_PCG_FLAGS"
.LASF0:
	.string	"signed char"
.LASF30:
	.string	"PG_reclaim"
.LASF53:
	.string	"/home/valerian/Documents/ba6/OS/repo/Scheduler/build-output"
.LASF11:
	.string	"_Bool"
.LASF33:
	.string	"PG_mlocked"
.LASF39:
	.string	"PG_slob_free"
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
