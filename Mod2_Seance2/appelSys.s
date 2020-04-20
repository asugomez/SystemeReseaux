	.file	"appelSys.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-96(%rbp), %rax
	movl	$80, %edx
	movq	%rax, %rsi
	movl	$0, %edi
	call	read@PLT
	movl	%eax, -104(%rbp)
	movl	-104(%rbp), %eax
	movslq	%eax, %rdx
	leaq	-96(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	write@PLT
	movl	%eax, -100(%rbp)
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
