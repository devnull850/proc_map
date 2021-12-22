	.section .data
msg:	.int	0x6c6c6548,0x57202c6f,0x646c726f,0xa21
	.section .text
	.globl bytes
bytes:	leaq	msg,%rdi
	movl	$0xe,%esi
	call	print
	xorl	%edi,%edi
	movl	$0x3c,%eax
	syscall
print:	pushq	%rbp
	movq	%rsp,%rbp
	addq	$0xfffffffffffffff0,%rsp
	movq	%rdi,-0x10(%rbp)
	movl	%esi,-0x4(%rbp)
	movl	$1,%edi
	movq	-0x10(%rbp),%rsi
	movl	-0x4(%rbp),%edx
	movl	$1,%eax
	syscall
	addq	$0x10,%rsp
	popq	%rbp
	ret
