/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:26:46 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/01/24 16:32:29 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include "libftprintf.h"

int	ft_switch(t_fmt *fmt, int *len_writen) {
	char *del;

	del = fmt->str;
	if (ft_strchr("diuUDoxOXp", fmt->specifier))
		*len_writen += write_decimal(fmt);
	else if (ft_strchr("csCS%", fmt->specifier))
		*len_writen += write_str(fmt);
//    else if (ft_strchr("cC", fmt->specifier))
//        return ;
//    else if (ft_strchr("sS", fmt->specifier))
//        return ;
	free(del);
	return (*len_writen);
}

// new version
unsigned    get_width(char *format)
{
    int      i;
    unsigned num;

    i = -1;
    num = 0;
    while (format[++i])
    {
        if (format[i] < '1' && format[i] > '9')
            continue ;
        if (format[i - 1] == '.')
            continue ;
        num = (unsigned)ft_atoi(format);
    }
    return (num);
}

//old version
//
//unsigned     get_width(char *format)
//{
//    int len;
//    char *num;
//    int number;
//
//    num = NULL;
//    len = (int)ft_strlen(format);
//    while (--len >= 0)
//        if (ft_isdigit(format[len]))
//        {
//            while (--len >= 0 && ft_isdigit(format[len]))
//				;
//			len = len < 0 ? 0 : len;
//			if (format[len] != '.')
//			{
//				num = format + len + (format[len] == '#' ? 1 : 0);
//				break ;
//			}
//        }
//	number = num != NULL ? ft_atoi(num) : 0;
//    return (number < 0 ? -((unsigned)number) : (unsigned)number);
//}

int		end_format(char	*format, t_fmt *fmt)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;
    size_t len = ft_strlen(CONVERSION);        // maybe change somethings for default
	unsigned char end_letter[] = "bkmtwyBKMTWY{|}~[]()@?>=</&!";
//    size_t len_end_letter = strlen(end_letter);
	// char skip[] = "qv_,:;";
	// n - bus error (flag in pdfs-bonus)
	// q - deprecated (you dont use this flag pds not inf about create functionals)
	// original function skip for this (flag q)
	// v - repeat in 16 overload (read man )
	//	a b c d e f g h i j k l m n o p q r s t u v w x y z
	i = -1;
	while (format[++i])
	{
		k = -1;
        j = -1;
		while (end_letter[++j])
        {
            if (++k == len)
            {
                j -= 1;
                k = -1;
                continue ;
            }
            if (CONVERSION[k] == format[i])
            {
                fmt->specifier = (unsigned char) CONVERSION[k];
                return (i + 1);
            }
            if (end_letter[j] == format[i])
            {
                //fmt->specifier = end_letter[j];
                return (i);
            }
        }
//		while(end_letter[j] && end_letter[j] != format[i])
//			j++;
//		if (j < strlen(end_letter))
//			return ((int)i);
//		while(CONVERSION[k] && CONVERSION[k] != format[i])
//			k++;
//		if (k < strlen(CONVERSION))
//			return (int(i));
	}
	return (0);
}

int		check_flag_zero(char *format)
{
	int i;

	i = -1;
	while (format[++i])
	{
		if (format[i] == '0')
			return (1);
		while(ft_strchr(".123456789", format[i]))
			i++;
	}
	return (0);
}

void	find_flags(char *format, t_fmt *data)
{
    if (ft_strchr(format, '-'))
        data->flag_first = '-';
    else if (check_flag_zero(format))
        data->flag_first = '0';
	if (data->specifier == '%')
		return ;
    if (ft_strchr(format, '+'))
        data->flag_second = '+';
    else if (ft_strchr(format, ' '))
        data->flag_second = ' ';
    if (ft_strchr(format, '#') && ft_strchr("oOxX", data->specifier))
        data->flag_second = '#';
}

// version 1.2
char		find_conversion(char *format)
{
    static char *conversion[] = {"z", "j", "ll", "l", "hh", "h"};
    int i;
//	char *p;

    i = -1;
    while (++i < 6)
        if (ft_strstr(format, conversion[i]))
        {
			//p = conversion[i];
            if (i == 2 || i == 4)
                return ((unsigned char)(conversion[i][0] << 1));
            else
                return (conversion[i][0]);
        }
    return (0);
}

int get_pression(char *format)
{
    char *tmp;
    int num;
	int i;

    //num = 0;
	i = 0;
    if ((tmp = ft_strrchr(format, '.')))
		while (*(tmp + i) && !ft_strchr("123456789", tmp[i]))
			i++;
	else
        return (-1);
    num = ft_atoi(tmp + i);
    return (num);
}

t_fmt *ft_clear(t_fmt *data)
{
	data->flag_first = '=';
	data->flag_second = '=';
	data->width = 0;
	data->precision = -1;
	data->modifier = 0;
	data->specifier = '=';
	data->str = NULL;
	return (data);
}

int     ft_printf(const char *format, ...)
{
    t_fmt	fmt;
    va_list	ap;
    int		read;
    size_t	i;
	int		end;

    read = 0;
    va_start(ap, format);
    while (*format)
        if (*format == '%' && format++)
        {
            i = 0;
            while (i < ft_strlen(format) && !ft_strchr(CONVERSION, format[i]))
				i++;
			ft_clear(&fmt);
			end = end_format((char *)format, &fmt);
			combination(ft_strncpy(ft_strnew(end), format, end), &fmt);
			compile_specifier_and_modifier(&ap, &fmt);
			ft_switch(&fmt, &read);
            format += (format[i]) ? end : i;
        }
        else
			read += write(1, format++, 1);
	va_end(ap);
    return (read);
}

size_t combination(char *str, t_fmt *fmt)
{
    char *del;
	size_t index = 0;
	//char *tmp;

    del = str;
    //ft_clear(fmt);
	//tmp = ft_strchr(CONVERSION, str[len - 1]);
    //fmt->specifier = tmp != NULL ? str[len - 1] : '=';
	//index = fmt->specifier != '=' ? (size_t)(str - tmp) : 0;
    find_flags(del,  fmt);
    fmt->width = get_width(del);
    fmt->precision = get_pression(str);
    fmt->modifier = (unsigned char)find_conversion(del);
	ft_strchr("cC%", fmt->specifier) ? fmt->str = ft_strnew(1) : 0;
    free(del);
	return (index);
//    return (fmt->specifier != 127 ? compile_specifier_and_modifier(p, *fmt) : 0);
}