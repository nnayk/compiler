	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 0
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	$0, -8(%rbp)
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	xorl	%eax, %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__Z3fooiii                      ## -- Begin function _Z3fooiii
	.p2align	4, 0x90
__Z3fooiii:                             ## @_Z3fooiii
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -16(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -8(%rbp)
	movl	$0, -4(%rbp)
	cmpl	$0, -16(%rbp)
	je	LBB1_6
## %bb.1:
	movl	$1, -4(%rbp)
	cmpl	$0, -12(%rbp)
	je	LBB1_5
## %bb.2:
	movl	$2, -4(%rbp)
	cmpl	$0, -8(%rbp)
	je	LBB1_4
## %bb.3:
	movl	$3, -4(%rbp)
LBB1_4:
	jmp	LBB1_5
LBB1_5:
	jmp	LBB1_6
LBB1_6:
	movl	-4(%rbp), %eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_x                              ## @x
.zerofill __DATA,__common,_x,4,2
	.globl	_y                              ## @y
.zerofill __DATA,__common,_y,4,2
.subsections_via_symbols
