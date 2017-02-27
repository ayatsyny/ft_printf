/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:14:04 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 00:16:07 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static intmax_t		convert_di(va_list *ap, t_fmt fmt)
{
	intmax_t num;

	num = va_arg(*ap, intmax_t);
	if (fmt.modifier == 'z')
		return ((size_t)num);
	else if (fmt.modifier == 'l' << 1)
		return ((long long)num);
	else if (fmt.modifier == 'l' || fmt.specifier == 'D')
		return ((long)num);
	else if (fmt.modifier == 'h')
		return ((short)num);
	else if (fmt.modifier == 'h' << 1)
		return ((signed char)num);
	else if (!fmt.modifier)
		return ((int)num);
	return (num);
}

static uintmax_t	convert_ox(va_list *ap, t_fmt fmt)
{
	uintmax_t num;

	num = va_arg(*ap, uintmax_t);
	if (fmt.modifier == 'z')
		return ((size_t)num);
	else if (fmt.modifier == 'l' << 1)
		return ((unsigned long long)num);
	else if (fmt.modifier == 'l' || ft_strchr("OU", fmt.specifier))
		return ((unsigned long)num);
	else if (fmt.modifier == 'h')
		return ((unsigned short)num);
	else if (fmt.modifier == 'h' << 1)
		return ((unsigned char)num);
	else if (!fmt.modifier)
		return ((unsigned)num);
	return (num);
}

void				compile_specifier_and_modifier(va_list *ap, t_fmt *fmt)
{
	if (ft_strchr("diD", fmt->specifier))
		fmt->str = ft_itoa_base(convert_di(ap, *fmt), fmt->specifier);
	else if (ft_strchr("uoxXUO", fmt->specifier))
		fmt->str = ft_itoa_base2(convert_ox(ap, *fmt), fmt->specifier);
	else if (fmt->specifier == 'p')
		fmt->str = ft_itoa_base2(va_arg(*ap, uintmax_t), fmt->specifier);
	else if (ft_strchr("scC%", fmt->specifier))
	{
		fmt->specifier == 'c' ? fmt->str[0] = (char)va_arg(*ap, int) : 0;
		fmt->specifier == 'C' ? fmt->str[0] = (char)va_arg(*ap, int) : 0;
		fmt->specifier == 's' ? fmt->str = va_arg(*ap, char*) : 0;
		fmt->specifier == '%' ? fmt->str[0] = '%' : 0;
	}
	else if (fmt->specifier == 'S')
		fmt->str = covert_to_char(va_arg(*ap, wchar_t*));
	else if (fmt->specifier != '=')
	{
		fmt->str[0] = fmt->specifier;
		fmt->specifier = 'c';
	}
}
