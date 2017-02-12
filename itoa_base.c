//
// Created by Andriy Yatsynyak on 2/3/17.
//
#include "libftprintf.h"
#define A(x) x < 0 ? -x : x

static void process_itoa(int value, int base, char *s, int *a)
{
    char value_str[] = "0123456789ABCDEF";

    if (value >= base)
        process_itoa(value / base, base, s, a);
    s[(*a)++] = value_str[A(value % base)];

}

char    *ft_itoa_base(int value, int base)
{
    int i;
    char *mas;
    //unsigned long long num;

    i = 0;
    if (!(mas = ft_strnew(35)))
        return (NULL);
    //num = (value < 0 && base == 10) ? -((unsigned long long)value) : ((unsigned long long)value);
    if (value < 0)
        mas[i++] = '-';
    process_itoa(value, base, mas, &i);
    return (mas);
}