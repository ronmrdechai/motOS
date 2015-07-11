#ifndef _IDT_H
#define _IDT_H

#define IDT_SIZE 256

/* An entry in the IDT table */
struct idt_entry_t
{
    unsigned short int base_lo;
    unsigned short int sel;
    unsigned char      zero;
    unsigned char      flags;
    unsigned short int base_hi;
} __attribute__ ((packed));

/* A pointer to the IDT */
struct idt_ptr_t {
    unsigned short int len;
    void              *ptr;
} __attribute__ ((packed));

/* Setup the IDT */
void setup_idt(void);

#endif /* ! defined(_IDT_H) */
