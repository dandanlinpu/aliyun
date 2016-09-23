	.file	"rio.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"tcp buf is empty or signal interupt read, cant not write data this time."
.LC1:
	.string	"rio_readn error"
.LC2:
	.string	"read all tcp buf data."
	.text
	.globl	rio_readn
	.type	rio_readn, @function
rio_readn:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -24(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L2
.L9:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rcx
	movl	-20(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read
	movl	%eax, -8(%rbp)
	cmpl	$-1, -8(%rbp)
	jne	.L3
	call	__errno_location
	movl	(%rax), %eax
	cmpl	$4, %eax
	je	.L4
	call	__errno_location
	movl	(%rax), %eax
	cmpl	$11, %eax
	jne	.L5
.L4:
	movl	$.LC0, %edi
	call	puts
	movl	$0, -8(%rbp)
	jmp	.L6
.L5:
	movl	$.LC1, %edi
	call	perror
	movl	$-1, %eax
	jmp	.L7
.L3:
	cmpl	$0, -8(%rbp)
	jne	.L6
	movl	$.LC2, %edi
	call	puts
	jmp	.L8
.L6:
	movl	-8(%rbp), %eax
	subl	%eax, -4(%rbp)
	movl	-8(%rbp), %eax
	cltq
	addq	%rax, -32(%rbp)
.L2:
	cmpl	$0, -4(%rbp)
	jg	.L9
.L8:
	movl	-4(%rbp), %eax
	movl	-24(%rbp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	rio_readn, .-rio_readn
	.section	.rodata
	.align 8
.LC3:
	.string	"tcp buf is full or signal interupt write, cant not write data this time."
.LC4:
	.string	"rio_writen error"
	.text
	.globl	rio_writen
	.type	rio_writen, @function
rio_writen:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -24(%rbp)
	movl	$0, -4(%rbp)
	movl	-24(%rbp), %eax
	movl	%eax, -8(%rbp)
	jmp	.L11
.L16:
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rcx
	movl	-20(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write
	movl	%eax, -4(%rbp)
	cmpl	$-1, -4(%rbp)
	jne	.L12
	call	__errno_location
	movl	(%rax), %eax
	cmpl	$11, %eax
	je	.L13
	call	__errno_location
	movl	(%rax), %eax
	cmpl	$4, %eax
	jne	.L14
.L13:
	movl	$.LC3, %edi
	call	puts
	movl	$0, -4(%rbp)
	jmp	.L12
.L14:
	movl	$.LC4, %edi
	call	perror
	movl	$-1, %eax
	jmp	.L15
.L12:
	movl	-4(%rbp), %eax
	subl	%eax, -8(%rbp)
	movl	-4(%rbp), %eax
	cltq
	addq	%rax, -32(%rbp)
.L11:
	cmpl	$0, -8(%rbp)
	jg	.L16
	movl	-24(%rbp), %eax
.L15:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	rio_writen, .-rio_writen
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-4)"
	.section	.note.GNU-stack,"",@progbits
