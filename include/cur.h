#ifndef _CUR_H
#define _CUR_H

#define CUR_MAX_X 80

struct cursor_t {
    unsigned char x;
    unsigned char y;
};

void cur_set(unsigned char x, unsigned char y);
void cur_advance(void);
void cur_nl(void);

#endif /* ! defined(_CUR_H) */
