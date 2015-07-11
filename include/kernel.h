#ifndef _KERNEL_H
#define _KERNEL_H

#define SOS_MAJOR_VERS 0
#define SOS_MINOR_VERS 1

extern void *heap_top;

void kmain(void) __attribute__ ((noreturn));

#endif /* !_KERNEL_H */
