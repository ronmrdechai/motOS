#ifndef _TERM_H
#define _TERM_H

#define TERM_PAGE_LINES   25
#define TERM_PAGE_COLUMNS 80
#define TERM_BUFFER_SIZE  (TERM_PAGE_LINES * TERM_PAGE_COLUMNS)

#define _term_init()        \
    do {                    \
        term_clear();       \
        term_refresh();     \
        term_sync_cursor(); \
    } while(0)

struct terminal_t { 
    unsigned char data[80 * 25];
    unsigned int pos;
};

#define TERM_SEG ((char*)0xb8000)

/* Refresh the terminal buffer, writing everything to the screen */
void term_refresh(void);
/* Clear the terminal buffer */
void term_clear(void);
/* Sync the cursor with the terminal position */
void term_sync_cursor(void);
/* "Write" a newline to the terminal */
void term_putnl(void);
/* Write a character to the terminal */
void term_putc(char c);
/* Write to the terminal */
void term_write(const char *c, unsigned int n);

#endif /* ! defined(_TERM_H) */
