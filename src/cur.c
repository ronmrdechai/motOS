#include <io.h>
#include <cur.h>

static struct cursor_t CURSOR = {.x = 0, .y = 0};

/** Cursor functions **/

/* Set the cursor position */
void cur_set(unsigned char x, unsigned char y)
{
    unsigned short pos = (y * CUR_MAX_X) + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
    CURSOR.x = x;
    CURSOR.y = y;
}

/* Advance the cursor by one */
void cur_advance(void)
{
    if (CURSOR.x == CUR_MAX_X - 1) {
        CURSOR.x = 0;
        CURSOR.y++;
    } else {
        CURSOR.x++;
    }
    cur_set(CURSOR.x, CURSOR.y);    
}

/* Push the cursor down one line */
void cur_nl(void)
{
    CURSOR.x = 0;
    CURSOR.y++;
    cur_set(CURSOR.x, CURSOR.y);    
}
