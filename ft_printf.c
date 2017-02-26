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

int	ft_switch(t_fmt *fmt, int *len_writen)
{
	char *del;

	del = NULL;
	if (ft_strchr("pdiuUD", fmt->specifier))
		*len_writen += write_decimal(fmt);
	else if (ft_strchr("oxOX", fmt->specifier))
		*len_writen += write_num_in_ox(fmt);
	else if (ft_strchr("csCS%", fmt->specifier) || fmt->specifier != '=')
		*len_writen += write_str(fmt);
//    else if (ft_strchr("cC", fmt->specifier))
//        return ;
//    else if (ft_strchr("sS", fmt->specifier))
//        return ;
	if (ft_strchr("diuUDoxOXp%cCS", fmt->specifier))
		del = fmt->str;
	free(del);
	return (*len_writen);
}

// new version
unsigned    get_width(char *format, t_fmt fmt)
{
    int      i;
	int		 j;
    unsigned num;

    i = -1;
    num = 0;
    while (format[++i])
    {
        if (!(format[i] >= '1' && format[i] <= '9'))
			continue ;
		if (format[i - 1] == '.')
		{
			while (format[i] >= '0' && format[i] <= '9')
				i++;
			continue ;
		}
		j = i;
		while (format[j] && format[j] >= '0' && format[j] <= '9')
			j++;
		if (i < j)
		{
			num = (unsigned) ft_atoi(format + i);
			i = j;
		}
    }
    return (num);
}

int end_format(char	*format, t_fmt *fmt, size_t index)
{
	fmt->specifier = format[index] ? (unsigned char)format[index] : '=';
	return ((int)index + 1);
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


unsigned int	ft_count_letter(char const *s, char c)
{
	int				i;
	unsigned int	count;

	i = -1;
	count = 0;
	while (s && s[++i])
		if (s[i] == c)
			count++;
	return (count);
}

// version 2
char		find_conversion(char *format)
{
	static char conversion[] = {'z', 'j', 'l', 'h'};
	int i;
	char *p;
	unsigned count;

	i = -1;
	while (++i < 4)
		if ((p = ft_strchr(format, conversion[i])))
		{
			if (i > 1)
				if ((count = ft_count_letter(p, conversion[i])))
					if (count % 2 == 0)
						return ((unsigned char)(conversion[i] << 1));
					if (count % 2)
						return (conversion[i]);
			else
				return (conversion[i]);
		}
	return (0);
}

int get_pression(char *format, t_fmt *fmt)
{
    char *tmp;
    int num;
	int i;

    //num = 0;
	i = 0;
    if ((tmp = ft_strrchr(format, '.')))
	{
		*(tmp + 1) == '-' ? (fmt->precision_flag = '-') : 0;
		while (*(tmp + i) && !ft_strchr("123456789", tmp[i]))
			i++;
	}
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
	data->precision_flag = 0;
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
            while (i < ft_strlen(format) && ft_strchr("-+0# hljz123456789.", format[i]))
				i++;
			ft_clear(&fmt);
			end = end_format((char *)format, &fmt, i);
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
	fmt->precision = get_pression(str, fmt);
    fmt->width = get_width(del, *fmt);
    fmt->modifier = (unsigned char)find_conversion(del);
	!ft_strchr("pdiuoxsDUOXS", fmt->specifier) ? fmt->str = ft_strnew(1) : 0;
//	ft_strchr("cC%", fmt->specifier) ? fmt->str = ft_strnew(1) : 0;
    free(del);
	return (index);
//    return (fmt->specifier != 127 ? compile_specifier_and_modifier(p, *fmt) : 0);
}