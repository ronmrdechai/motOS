#ifndef _GDT_H
#define _GDT_H

/*
 * A constuctor for conventional GDT entries. Shamelessly copied from the Linux
 * kernel source code (arch/x86/include/asm/segment.h).
 *
 * See the Intel developers manual for more info.
 */
#define GDT_ENTRY(flags, base, limit)        \
        ((((base)  & 0xFF000000ULL) << 32) | \
         (((flags) & 0x0000F0FFULL) << 40) | \
         (((limit) & 0x000F0000ULL) << 32) | \
         (((base)  & 0x00FFFFFFULL) << 16) | \
         (((limit) & 0x0000FFFFULL)))

#define GDT_ENTRIES 3

/* 
 * An entry in the GDT table, some people define this as a struct of some kind,
 * but really it is just a 64-bit integer
 */
typedef unsigned long long int gdt_entry_t;

/* A pointer to the GDT table */
struct gdt_ptr_t {
    unsigned short int len;
    void              *ptr;
} __attribute__ ((packed));

/* Setup a basic GDT */
void setup_gdt(void);

#endif /* ! defined(_GDT_H) */

