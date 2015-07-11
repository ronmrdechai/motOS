#include <kernel.h>
#include <printf.h>
#include <term.h>
#include <idt.h>
#include <gdt.h>
#include <mm.h>
#include <io.h>

void kmain(void)
{
    setup_idt();
    setup_gdt();
    _term_init();

    /* Not an actual prompt yet... */
    kprintf("> ");

    while (1) term_refresh();
}
