#include <printf.h>
#include <term.h>

static unsigned int __kputc(char c)
{
    term_putc(c);
    return 1;
}

static unsigned int __kputs(const char *c)
{
    unsigned long int start = (unsigned long int)c;
    while (*c != '\0') {
        term_putc(*c);
        ++c;
    }
    return (unsigned int)(c - start);
}

static unsigned int __kputi(long int num, char sign)
{
    char str[11];
    unsigned int size = 0;

    if (num == 0) {
        str[size++] = '0';
    } else {
        if (num < 0 && sign) {
            str[size++] = '-';
            num = -num;
        }
        int len = 0;
        for (unsigned long int i = num; i; i /= 10)
            ++len;
        for (int i = len; i; --i) {
            int div = 1;
            for (int j = i; j > 1; --j) div *= 10;
            str[size++] = ('0' + ((num / div) % 10));
        }
    }

    term_write(str, size);
    return size;
}

static unsigned int __kputh(unsigned long int num, char upper)
{
    char str[8];
    char *lookup = (upper) ? "0123456789ABCDEF" : "0123456789abcdef";
    unsigned int size = 0;
    unsigned int pos = 0;

    for (unsigned long int i = num; i; i >>= 4) pos++;
    size = pos;

    for (unsigned long int i = num; i; i >>= 4) {
        int nibble = i & 0x0F;
        str[--pos] = lookup[nibble];
    }
    term_write(str, size);
    return size;
}

unsigned int kprintf(const char *fmt, ...)
{
    void *args = &fmt;
    unsigned int len = 0;
    unsigned int *n;

    args = ((char **)args) + 1;
    while (*fmt != '\0') {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case '%':
                    len += __kputc('%');
                    break;
                case 'd':
                case 'i':
                    len += __kputi(*((int *)args), 1);
                    args = ((int *)args) + 1;
                    break;
                case 'u':
                    len += __kputi(*((int *)args), 0);
                    args = ((int *)args) + 1;
                    break;
                case 'x':
                    len += __kputh(*((int *)args), 0);
                    args = ((int *)args) + 1;
                    break;
                case 'X':
                    len += __kputh(*((int *)args), 1);
                    args = ((int *)args) + 1;
                    break;
                case 'c':
                    len += __kputc(*((char *)args));
                    args = ((char **)args) + 1;
                    break;
                case 's':
                    len += __kputs(*((char **)args));
                    args = ((char **)args) + 1;
                    break;
                case 'n':
                    n = *((unsigned int **)args);
                    *n = len;
                    args = ((unsigned int **)args) + 1;
                    break;
                default:
                    len += __kputc('%');
                    len += __kputc(*fmt);
                    break;
            }
            fmt++;
        } else {
            len += __kputc(*fmt);
            fmt++;
        }
    }
    term_sync_cursor();
    return len;
}
