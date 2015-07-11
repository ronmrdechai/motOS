	.file	"main.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"> "
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.text
.LHOTB1:
	.align 16
	.globl	kmain
	.type	kmain, @function
kmain:
.LFB4:
	.cfi_startproc
	subl	$12, %esp
	.cfi_def_cfa_offset 16
	call	setup_idt
	call	setup_gdt
	call	term_clear
	call	term_refresh
	call	term_sync_cursor
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	$.LC0
	.cfi_def_cfa_offset 32
	call	kprintf
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	.align 16
.L2:
	call	term_refresh
	jmp	.L2
	.cfi_endproc
.LFE4:
	.size	kmain, .-kmain
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.ident	"GCC: (GNU) 5.1.0"
