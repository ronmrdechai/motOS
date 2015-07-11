#include <idt.h>

static struct idt_entry_t idt_entries[IDT_SIZE] = {0};
static struct idt_ptr_t   idt;

static void idt_set(struct idt_entry_t *idte,
                    unsigned int addr, 
                    unsigned short int sel,
                    unsigned char flags)
{
    idte->base_lo = (addr & 0xFFFF);
    idte->sel   = sel;
    idte->zero  = 0;
    idte->flags = flags;
    idte->base_hi = ((addr & 0xFFFF0000) >> 16);
}

void setup_idt(void)
{
    idt.len = sizeof(idt_entries) - 1;
    idt.ptr = &idt_entries;
    __asm__ __volatile__("lidtl %0" : : "m" (idt));
}
