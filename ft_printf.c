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
#include <string.h>

int	ft_switch(t_fmt *fmt, int *len_writen)
{
    if (ft_strchr("diuUDoxOXp", fmt->specifier))
        *len_writen += write_decimal(fmt);
	else if (ft_strchr("cs%", fmt->specifier))
		*len_writen += write_str(fmt);
//    else if (ft_strchr("cC", fmt->specifier))
//        return ;
//    else if (ft_strchr("sS", fmt->specifier))
//        return ;
	return (*len_writen);
}

unsigned     get_width(char *format)
{
    int len;
    int f_end;
    char *num;
    int number;

    num = NULL;
    number = 0;
    if (!format)
        return (0);
    len = (int)ft_strlen(format) - 1;
    while (--len > 0)
        if (isdigit(format[len]))
        {
            f_end = len--;
            while (len > 0 && ft_isdigit(format[len]))
                 len--;
            if (len < f_end && format[f_end - len] != '0')
            {
                num = ft_strsub(format, (unsigned)(len + 1), (size_t)f_end - len);
                break ;
            }
        }
    if (num)
        number = atoi(num);
    free(num);
    return ((unsigned)number);
}

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

int		find_zero(char *format)
{
	int i;
	int res;
	int f;

	i = -1;
	f = 0;
	while (format[++i])
	{
		res = ft_isdigit(format[i]);
		if (res != 0)
		{
			if (res != '0' && !f)
				f = 1;
			else if (res == '0' && !f)
				return (1);
			else if (res == 0)
				f = 0;
		}
	}
	return (0);
}

void	find_flags(char *format, t_fmt *data)
{
    if (strchr(format, '-'))
        data->flag_first = '-';
    else if (find_zero(format))
        data->flag_first = '0';
    if (strchr(format, '+'))
        data->flag_second = '+';
    else if (strchr(format, ' '))
        data->flag_second = ' ';
    if (ft_strchr(format, '#') && ft_strchr("oOxX", data->specifier))
        data->flag_second = '#';
}

// version 1.2
char		find_conversion(char *format)
{
    static char *conversion[] = {"hh", "h", "ll", "l", "j", "z"};
    int i;
	//char *p;

    i = -1;
    while (++i < 6)
        if (strstr(format, conversion[i]))
        {
			//p = conversion[i];
            if (i == 0 || i == 2)
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

    num = 0;
	i = 0;
    if ((tmp = ft_strrchr(format, '.')))
		while (*(tmp + i) && !ft_strchr("123456789", tmp[i]))
			i++;
	else
        return (num);
    num = ft_atoi(tmp + i);
    return (num);
}


// todo you need change libft fot ft_strsub
char	*test_strsub(char	const *s, unsigned int start, size_t len)
{
    char	*fresh;
    size_t	i;

    i = 0;
    if (!s || start > (unsigned)len || (size_t)start > ft_strlen(s)
        || (int)start <= -1)
        return (NULL);
    fresh = (char *)malloc(len + 1);
    if (!fresh)
        return (NULL);
    s += start;
    while (s && i < len)
        fresh[i++] = *(char *)s++;
    fresh[i] = '\0';
    return (fresh);
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
    t_fmt 		fmt;
    va_list     ap;
    int    read;
    size_t         i;
	int			end;

    read = 0;
    i = 0;
    va_start(ap, format);
    while (*format)
    {
        if (*format == '%' && format++)
        {
            i = 0;
            while (i < ft_strlen(format) && !ft_strchr("0123456789hljz-+0# ", format[i]))
                i++;
			ft_clear(&fmt);
			end = end_format((char *) format, &fmt);
			combination(ft_strncpy(ft_strnew(end), format, end), &fmt);

			compile_specifier_and_modifier(&ap, &fmt);
			ft_switch(&fmt, &read);
            format += (format[i]) ? end : i;
        }
        else
		{
			ft_putchar(*format++);
			read++;
		}
    }
	va_end(ap);
    return (read);

}

size_t combination(char *str, t_fmt *fmt)
{
    char *del;
    int len;
	size_t index = 0;
	//char *tmp;

    del = str;
    len = (int)ft_strlen(str);
    //ft_clear(fmt);
	//tmp = ft_strchr(CONVERSION, str[len - 1]);
    //fmt->specifier = tmp != NULL ? str[len - 1] : '=';
	//index = fmt->specifier != '=' ? (size_t)(str - tmp) : 0;
    find_flags(del,  fmt);
    fmt->width = get_width(del);
    fmt->precision = get_pression(str);
    fmt->modifier = (unsigned char)find_conversion(del);
    free(del);
	return (index);
//    return (fmt->specifier != 127 ? compile_specifier_and_modifier(p, *fmt) : 0);
}