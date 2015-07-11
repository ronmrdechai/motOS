#include <gdt.h>

static gdt_entry_t gdt_entries[GDT_ENTRIES] __attribute__((aligned(16)));
static struct gdt_ptr_t gdt;

void setup_gdt(void)
{
    /* null */
    gdt_entries[0] = GDT_ENTRY(0, 0, 0);
    /* data */
    gdt_entries[1] = GDT_ENTRY(0xCF92, 0, 0xFFFFFFFF);
    /* code */
    gdt_entries[2] = GDT_ENTRY(0xCF9A, 0, 0xFFFFFFFF);
    gdt.len = sizeof(gdt_entries) - 1;
    gdt.ptr = &gdt_entries;
    __asm__ __volatile__("lgdtl %0" : : "m" (gdt));
}
