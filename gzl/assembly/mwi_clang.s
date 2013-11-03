section .text
        global _begin
_begin:
	movq	%rdi, -8(%rsp)
	movq	%rsi, -16(%rsp)
	movl	%edx, -20(%rsp)
	movl	$0, -24(%rsp)
	movl	$1, -28(%rsp)
.loop:
	cmpl	$30, -28(%rsp)
	jge .end
	movabsq	$30, %rax
	cvtsi2sdq	%rax, %xmm0
	movslq	-28(%rsp), %rax
	movq	-8(%rsp), %rcx
	cvtsi2sd	(%rcx,%rax,4), %xmm1
	divsd	%xmm0, %xmm1
	cvtsi2sd	-24(%rsp), %xmm0
	addsd	%xmm1, %xmm0
	cvttsd2si	%xmm0, %edx
	movl	%edx, -24(%rsp)
	movl	-28(%rsp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rsp)
	jmp	.loop
.end:
	movl	-24(%rsp), %eax
	ret

    movq
	movl
	cmpl
	jge
	movabsq
	cvtsi2sdq
	movslq
	cvtsi2sd
	divsd
	addsd
	cvttsd2si
	addl
	jmp
	ret
