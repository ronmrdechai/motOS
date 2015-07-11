.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO 
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384
stack_top:

.section .kernel_heap , "aw", @nobits
.global heap_top
.type heap_top, @object
heap_top:
.skip 16384
heap_bottom:

.section .text
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp
    cli
    call kmain
    hlt
.lhang:
    jmp .lhang
