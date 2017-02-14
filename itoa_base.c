//
// Created by Andriy Yatsynyak on 2/3/17.
//
#include "libftprintf.h"
#define A(x) x < 0 ? -x : x

static void process_itoa(intmax_t value, int base, char *s, int *a)
{
    char value_str[] = "0123456789ABCDEF";

    if (value >= base)
        process_itoa(value / base, base, s, a);
    s[(*a)++] = value_str[A(value % base)];

}

static int get_base(char letter)
{
	int num;

	num = 0;
	if (ft_strchr("diD", letter))
		num = 10;
	else if (ft_strchr("pxX", letter))
		num = 16;
	else if (ft_strchr("oO", letter))
		num = 8;
	return (num);
}

char    *ft_itoa_base(intmax_t value, char base_specifier)
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
    process_itoa(value, get_base(base_specifier), mas, &i);
    return (mas);
}