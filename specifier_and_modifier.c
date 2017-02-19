//
// Created by Andriy Yatsynyak on 2/3/17.
//

#include "libftprintf.h"

static intmax_t		convert_di(va_list *ap, t_fmt fmt)
{
	intmax_t num;

	num = va_arg(*ap, intmax_t);
	if (fmt.modifier == 'h' << 1)
		num = (signed char)num;
	else if (fmt.modifier == 'h')
		num = (short int)num;
	else if (fmt.modifier == 'l' || fmt.specifier == 'D')
		num = (long int)num;
	else if (fmt.modifier == 'l' << 1)
		num = (long long int)num;
//	else if (fmt.modifier == 'j')
//		num = (size_t)num;
	else if (fmt.modifier == 'z')
		num = (size_t)num;
	else if (!fmt.modifier)
		num = (int)num;
	return (num);
}
static uintmax_t convert_ox(va_list *ap, t_fmt fmt)
{
	uintmax_t num;

	num = va_arg(*ap, uintmax_t);
	if (fmt.modifier == 'h' << 1)
		num = (unsigned char)num;
	else if (fmt.modifier == 'h')
		num = (unsigned short int)num;
	else if (fmt.modifier == 'l' || ft_strchr("OU", fmt.specifier))
		num = (unsigned long int)num;
	else if (fmt.modifier == 'l' << 1)
		num = (unsigned long long int)num;
	else if (fmt.modifier == 'z')
		num = (size_t)num;
	else if (!fmt.modifier)
		num = (unsigned int)num;
	return (num);
}

void    compile_specifier_and_modifier(va_list *ap, t_fmt *fmt)
{
    if (ft_strchr("diD", fmt->specifier))
		fmt->str = ft_itoa_base(convert_di(ap, *fmt), fmt->specifier);
	else if(ft_strchr("puoxXUO", fmt->specifier))
		fmt->str = ft_itoa_base(convert_ox(ap, *fmt), fmt->specifier);
	else if (ft_strchr("s", fmt->specifier))
	{
		fmt->str = va_arg(*ap, char *);
		cal_letter(fmt);
	}
	else if (ft_strchr("c%", fmt->specifier))
	{
		fmt->str[0] = va_arg(*ap, int);
		cal_letter(fmt);
	}
}