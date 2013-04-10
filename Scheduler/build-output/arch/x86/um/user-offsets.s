	.file	"user-offsets.c"
# GNU C (Ubuntu/Linaro 4.7.2-2ubuntu1) version 4.7.2 (x86_64-linux-gnu)
#	compiled by GNU C version 4.7.2, GMP version 5.0.2, MPFR version 3.1.0-p3, MPC version 0.9
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passées: 
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/shared
# -I /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/um/include/shared/skas
# -I arch/x86/include/generated -imultiarch x86_64-linux-gnu -D __arch_um__
# -D vmap=kernel_vmap -D in6addr_loopback=kernel_in6addr_loopback
# -D in6addr_any=kernel_in6addr_any -D strrchr=kernel_strrchr
# -D _LARGEFILE64_SOURCE -D CC_HAVE_ASM_GOTO -D _FILE_OFFSET_BITS=64
# -D _GNU_SOURCE -D _LARGEFILE64_SOURCE -idirafter include
# -MD arch/x86/um/.user-offsets.s.d
# /home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c
# -mcmodel=large -m64 -mtune=generic -march=x86-64
# -auxbase-strip arch/x86/um/user-offsets.s -g -Os -Wall -Wundef
# -Wstrict-prototypes -Wno-trigraphs -Werror=implicit-function-declaration
# -Wno-format-security -Wframe-larger-than=1024
# -Wno-unused-but-set-variable -Wdeclaration-after-statement
# -Wno-pointer-sign -fno-strict-aliasing -fno-common
# -fno-delete-null-pointer-checks -fno-builtin -funit-at-a-time
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
.LFB33:
	.file 1 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c"
	.loc 1 32 0
	.cfi_startproc
	pushq	%rbp	#
.LCFI0:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
.LCFI1:
	.cfi_def_cfa_register 6
	.loc 1 55 0
#APP
# 55 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_FP_SIZE $64 sizeof(struct _fpstate) / sizeof(unsigned long)	#
# 0 "" 2
	.loc 1 56 0
# 56 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_BX $5 RBX	#
# 0 "" 2
	.loc 1 57 0
# 57 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_CX $11 RCX	#
# 0 "" 2
	.loc 1 58 0
# 58 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_DI $14 RDI	#
# 0 "" 2
	.loc 1 59 0
# 59 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_SI $13 RSI	#
# 0 "" 2
	.loc 1 60 0
# 60 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_DX $12 RDX	#
# 0 "" 2
	.loc 1 61 0
# 61 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_BP $4 RBP	#
# 0 "" 2
	.loc 1 62 0
# 62 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_AX $10 RAX	#
# 0 "" 2
	.loc 1 63 0
# 63 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_R8 $9 R8	#
# 0 "" 2
	.loc 1 64 0
# 64 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_R9 $8 R9	#
# 0 "" 2
	.loc 1 65 0
# 65 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_R10 $7 R10	#
# 0 "" 2
	.loc 1 66 0
# 66 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_R11 $6 R11	#
# 0 "" 2
	.loc 1 67 0
# 67 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_R12 $3 R12	#
# 0 "" 2
	.loc 1 68 0
# 68 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_R13 $2 R13	#
# 0 "" 2
	.loc 1 69 0
# 69 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_R14 $1 R14	#
# 0 "" 2
	.loc 1 70 0
# 70 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_R15 $0 R15	#
# 0 "" 2
	.loc 1 71 0
# 71 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_ORIG_AX $15 ORIG_RAX	#
# 0 "" 2
	.loc 1 72 0
# 72 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_CS $17 CS	#
# 0 "" 2
	.loc 1 73 0
# 73 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_SS $20 SS	#
# 0 "" 2
	.loc 1 74 0
# 74 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_EFLAGS $18 EFLAGS	#
# 0 "" 2
	.loc 1 82 0
# 82 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_IP $16 RIP	#
# 0 "" 2
	.loc 1 83 0
# 83 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->HOST_SP $19 RSP	#
# 0 "" 2
	.loc 1 86 0
# 86 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->UM_FRAME_SIZE $216 sizeof(struct user_regs_struct)	#
# 0 "" 2
	.loc 1 87 0
# 87 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->UM_POLLIN $1 POLLIN	#
# 0 "" 2
	.loc 1 88 0
# 88 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->UM_POLLPRI $2 POLLPRI	#
# 0 "" 2
	.loc 1 89 0
# 89 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->UM_POLLOUT $4 POLLOUT	#
# 0 "" 2
	.loc 1 91 0
# 91 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->UM_PROT_READ $1 PROT_READ	#
# 0 "" 2
	.loc 1 92 0
# 92 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->UM_PROT_WRITE $2 PROT_WRITE	#
# 0 "" 2
	.loc 1 93 0
# 93 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->UM_PROT_EXEC $4 PROT_EXEC	#
# 0 "" 2
	.loc 1 95 0
# 95 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->__NR_syscall_max $313 sizeof(syscalls) - 1	#
# 0 "" 2
	.loc 1 96 0
# 96 "/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c" 1
	
->NR_syscalls $314 sizeof(syscalls)	#
# 0 "" 2
	.loc 1 97 0
#NO_APP
	popq	%rbp	#
.LCFI2:
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE33:
	.size	foo, .-foo
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xb8
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF11
	.byte	0x1
	.long	.LASF12
	.long	.LASF13
	.quad	.Ltext0
	.quad	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF7
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF10
	.uleb128 0x4
	.byte	0x1
	.string	"foo"
	.byte	0x1
	.byte	0x1f
	.byte	0x1
	.quad	.LFB33
	.quad	.LFE33
	.long	.LLST0
	.byte	0x1
	.uleb128 0x5
	.long	0x6c
	.long	0xb0
	.uleb128 0x6
	.long	0x65
	.value	0x139
	.byte	0
	.uleb128 0x7
	.long	.LASF14
	.byte	0x1
	.byte	0x14
	.long	0x9f
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
	.uleb128 0x5
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.quad	.LFB33-.Ltext0
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
	.quad	.LFE33-.Ltext0
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
.LASF10:
	.string	"long long int"
.LASF13:
	.string	"/home/valerian/Documents/ba6/OS/repo/Scheduler/build-output"
.LASF3:
	.string	"unsigned int"
.LASF11:
	.string	"GNU C 4.7.2"
.LASF0:
	.string	"long unsigned int"
.LASF12:
	.string	"/home/valerian/Documents/ba6/OS/repo/Scheduler/linux-3.8.3/arch/x86/um/user-offsets.c"
.LASF9:
	.string	"long long unsigned int"
.LASF1:
	.string	"unsigned char"
.LASF8:
	.string	"char"
.LASF6:
	.string	"long int"
.LASF14:
	.string	"syscalls"
.LASF2:
	.string	"short unsigned int"
.LASF4:
	.string	"signed char"
.LASF5:
	.string	"short int"
.LASF7:
	.string	"sizetype"
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
