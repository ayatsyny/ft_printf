//
// Created by Andriy Yatsynyak on 2/3/17.
//

#include "libftprintf.h"

static intmax_t		convert_di(va_list *ap, t_fmt fmt)
{
	intmax_t num;

	num = va_arg(*ap, intmax_t);
	if (fmt.modifier == 'z')
		num = (size_t)num;
	else if (fmt.modifier == 'l' << 1)
		num = (long long)num;
	else if (fmt.modifier == 'l' || fmt.specifier == 'D')
		num = (long)num;
	else if (fmt.modifier == 'h')
		num = (short)num;
	else if (fmt.modifier == 'h' << 1)
		num = (signed char)num;
//	else if (fmt.modifier == 'j')
//		num = (size_t)num;
	else if (!fmt.modifier)
		num = (int)num;
	return (num);
}
static uintmax_t convert_ox(va_list *ap, t_fmt fmt)
{
	uintmax_t num;

	num = va_arg(*ap, uintmax_t);
	if (fmt.modifier == 'z')
		num = (size_t)num;
	else if (fmt.modifier == 'l' << 1)
		num = (unsigned long long)num;
	else if (fmt.modifier == 'l' || ft_strchr("OU", fmt.specifier))
		num = (unsigned long)num;
	else if (fmt.modifier == 'h')
		num = (unsigned short)num;
	else if (fmt.modifier == 'h' << 1)
		num = (unsigned char)num;
//	else if (fmt.modifier == 'j')
//		num = (uintmax_t)num;
	else if (!fmt.modifier)
		num = (unsigned)num;
	return (num);
}

void    compile_specifier_and_modifier(va_list *ap, t_fmt *fmt)
{
    if (ft_strchr("diD", fmt->specifier))
		fmt->str = ft_itoa_base(convert_di(ap, *fmt), fmt->specifier);
	else if(ft_strchr("puoxXUO", fmt->specifier))
		fmt->str = ft_itoa_base2(convert_ox(ap, *fmt), fmt->specifier);
	else if (ft_strchr("scC%", fmt->specifier))
	{
		fmt->specifier == 'c' ? fmt->str[0] = (char)va_arg(*ap, int) : 0;
		fmt->specifier == 'C' ? fmt->str[0] = (char)va_arg(*ap, int) : 0;
		fmt->specifier == 's' ? fmt->str = va_arg(*ap, char*) : 0;
//		fmt->specifier == 'S' ? fmt->str = va_arg(*ap, wchar_t*) : 0;
		fmt->specifier == '%' ? fmt->str[0] = '%' : 0;
		cal_letter(fmt);
	}
	else if (fmt->specifier == 'S')
		fmt->str = covert_to_char(va_arg(*ap, wchar_t*));

}