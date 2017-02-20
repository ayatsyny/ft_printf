//
// Created by Andriy Yatsynyak on 2/3/17.
//
#include "libftprintf.h"
#define A(x) x < 0 ? -x : x

static void process_itoa(intmax_t value, int base, char *s, int *a)
{
    char value_str[] = "0123456789ABCDEF";

    if (value >= base || value <= -base)
        process_itoa(value / base, base, s, a);
    s[(*a)++] = value_str[A(value % base)];

}

static void process_itoa2(uintmax_t value, uintmax_t base, char *s, int *a)
{
	char value_str[] = "0123456789ABCDEF";

	if (value >= base)
		process_itoa2(value / base, base, s, a);
	s[(*a)++] = value_str[value % base];
}

static int get_base(char letter)
{
	int num;

	num = 0;
	if (ft_strchr("duiDU", letter))
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
	int	base;
	uintmax_t val;

    i = 0;
    if (!(mas = ft_strnew(35)))
        return (NULL);
	base = get_base(base_specifier);
    if (value < 0)
	{
		base == 10 ? mas[i++] = '-' : 0;
		val = -((uintmax_t)value);
		process_itoa2(val, (uintmax_t)base, mas, &i);
	}
	else
		process_itoa(value, base, mas, &i);
	mas[i] = '\0';
    return (mas);
}