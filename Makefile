INCLUDEDIR ?= include
OBJDIR     ?= obj
SRCDIR     ?= src
ARCHDIR    ?= arch/i386
CFLAGS     ?= -std=c99 -O2 -ffreestanding -nostdlib -lgcc
CFLAGS     := $(CFLAGS) -Wall -Wextra -I$(INCLUDEDIR)
LDFLAGS    ?=

CC = i686-elf-gcc

SOURCES = main.c boot.c cur.c term.c printf.c mm.c gdt.c idt.c
OBJECTS = $(SOURCES:%.c=$(OBJDIR)/%.o)
KERNEL  = k32.bin

TAGSFILE = tags
TAGSARGS = -R --c++-kinds=+p --fields=+iaS --extra=+q --languages=C,C++,Asm 

.PHONY: default all clean cleanall run rundebug

default: $(KERNEL)
all: $(KERNEL) $(TAGSFILE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) 

$(OBJDIR)/%.o: $(SRCDIR)/%.S
	$(CC) -c $< -o $@ $(CFLAGS) 

$(KERNEL): $(OBJECTS) $(ARCHDIR)/link.ld
	$(CC) -T $(ARCHDIR)/link.ld -o $@ $(OBJECTS) $(CFLAGS) $(LDFLAGS)

$(TAGSFILE): $(SRCDIR)/*.S $(SRCDIR)/*.c $(INCLUDEDIR)/*.h
	exctags -o $@ $(TAGSARGS) .

clean:
	rm -f $(KERNEL) $(OBJECTS)

cleanall: clean
	rm -f $(TAGSFILE)

run: $(KERNEL)
	qemu-system-i386 -kernel $< 

rundebug: $(KERNEL)
	qemu-system-i386 -s -kernel $< &
	gdb -iex "target remote localhost:1234"
