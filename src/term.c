#include <cur.h>
#include <term.h>

static struct terminal_t TERMINAL = {.data = {0}, .pos = 0};

void term_refresh(void)
{
    unsigned int i = 0;
    unsigned int j = 0;
    while (i < TERM_BUFFER_SIZE * 2) {
        TERM_SEG[i] = TERMINAL.data[j];
        TERM_SEG[i + 1] = 0x07;         
        i = i + 2;
        j++;
    }
}

void term_clear(void)
{
    unsigned int i = 0;
    while (i < TERM_BUFFER_SIZE) {
        TERMINAL.data[i++] = ' ';
    }
    TERMINAL.pos = 0;
}

void term_sync_cursor(void)
{
    cur_set(TERMINAL.pos % TERM_PAGE_COLUMNS,
            TERMINAL.pos / TERM_PAGE_COLUMNS);
}

void term_putnl(void)
{
    TERMINAL.pos = TERMINAL.pos + TERM_PAGE_COLUMNS -
        (TERMINAL.pos % TERM_PAGE_COLUMNS);
}

void term_putc(char c)
{
    if (c == '\n') {
        term_putnl();
    } else {
        TERMINAL.data[TERMINAL.pos++] = c;
    }
    unsigned int pos_line = (TERMINAL.pos / TERM_PAGE_COLUMNS);
    if (pos_line >= TERM_PAGE_LINES) {
        term_clear();
    }
}

void term_write(const char *c, unsigned int n)
{
    while (n--) {
        term_putc(*c);
        ++c;
    }
}
