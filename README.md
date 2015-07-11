# motOS - My attempt at writing an operating system

This is my attempt at writing an operating system. It currently doesn't do much,
but the idea is to, at some point, embed a FORTH/LISP interpreter (I haven't
decided yet) in the kernel, and write the rest of it in a higher level language.

# Building

To build you need an i686-elf gcc cross compiler. I suggest reading the 
[tutorial](http://wiki.osdev.org/GCC_Cross-Compiler) on OSDev about how to
build one.

To build the kernel just run `make`. You can run the kernel in QEMU using `make
run`. I'll probably add a target to build a floppy image soon.
