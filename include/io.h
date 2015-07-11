#ifndef _IO_H
#define _IO_H

#define __inline inline __attribute__ ((always_inline))

/* I/O port interface functions.
 * These functions expose the in/out opcodes to the C source code.
 */

static __inline unsigned char inb(unsigned short int port)
{
    unsigned char v;
    __asm__ __volatile__ ("inb %w1,%0":"=a" (v):"Nd" (port));
    return v;
}

static __inline unsigned short int inw (unsigned short int port)
{
    unsigned short v;
    __asm__ __volatile__ ("inw %w1,%0":"=a" (v):"Nd" (port));
    return v;
}

static __inline void outb(unsigned short int port, unsigned char value)
{
    __asm__ __volatile__ ("outb %b0,%w1": :"a" (value), "Nd" (port));
}

static __inline void outw (unsigned short int value, unsigned short int port)
{
    __asm__ __volatile__ ("outw %w0,%w1": :"a" (value), "Nd" (port));
}

#endif /* ! defined(_IO_H) */
