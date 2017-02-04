//
// Created by Andriy Yatsynyak on 2/3/17.
//
#include "libftprintf.h"

static void process_itoa(unsigned long long value, unsigned long long base, char *s, int *a)
{
    char value_str[] = "0123456789ABCDEF";

    if (value > base)
        process_itoa(value / base, base, s, a);
    s[(*i)++] = value_str[value % base];

}

char    *ft_itoa(int value, int base)
{
    int i;
    char *mas;
    unsigned long long num;

    i = 0;
    if (2 < base || base > 16 || !(mas = ft_strnew(35)))
        return (NULL);
    num = (value < 0) ? -((unsigned long long)value) : ((unsigned long long)value);
    if (value < 0)
        mas[i++] = '-';
    process_itoa(num, (unsigned long long)base, mas, i);
    return (mas);
}