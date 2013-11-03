apply_mwi:

        .LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	$0, -8(%rbp)
	movl	$1, -4(%rbp)
	jmp	.L10
.L11:
	cvtsi2sd	-8(%rbp), %xmm1
	movl	-4(%rbp), %eax
	cltq
	salq	$2, %rax
	addq	-24(%rbp), %rax
	movl	(%rax), %eax
	cvtsi2sd	%eax, %xmm0
	movsd	.LC0(%rip), %xmm2
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	cvttsd2si	%xmm0, %eax
	movl	%eax, -8(%rbp)
	addl	$1, -4(%rbp)
.L10:
	cmpl	$29, -4(%rbp)
	jle	.L11
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	apply_mwi, .-apply_mwi
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1077805056
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
