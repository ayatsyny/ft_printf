/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:08:40 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 00:11:53 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned		get_width(char *format, unsigned num)
{
	int			i;
	int			j;

	i = -1;
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
			num = (unsigned)ft_atoi(format + i);
			i = j;
		}
	}
	return (num);
}

void			find_flags(char *format, t_fmt *data)
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

unsigned char	get_modifier(char *format)
{
	static unsigned char	conversion[] = {'z', 'j', 'l', 'h'};
	unsigned				count;
	char					*p;
	int						i;

	i = -1;
	while (++i < 4)
		if ((p = ft_strchr(format, conversion[i])))
		{
			if (i > 1 && (count = count_letters(p, conversion[i])))
			{
				if (count % 2 == 0)
					return (conversion[i] << 1);
				if (count % 2)
					return (conversion[i]);
			}
			else
				return (conversion[i]);
		}
	return (0);
}

int				get_pression(char *format, t_fmt *fmt)
{
	char	*tmp;
	int		i;

	i = 0;
	if ((tmp = ft_strrchr(format, '.')))
	{
		*(tmp + 1) == '-' ? (fmt->precision_flag = '-') : 0;
		while (*(tmp + i) && !ft_strchr("123456789", tmp[i]))
			i++;
	}
	else
		return (-1);
	return (ft_atoi(tmp + i));
}

void			combination(const char *str, t_fmt *fmt, size_t index)
{
	unsigned	num;
	char		*copy_str;

	num = 0;
	init_s_fmt(fmt);
	fmt->specifier = str[index] ? (unsigned char)str[index] : '=';
	index++;
	copy_str = ft_strsub(str, 0, index);
	find_flags(copy_str, fmt);
	fmt->precision = get_pression(copy_str, fmt);
	fmt->width = get_width(copy_str, num);
	fmt->modifier = get_modifier(copy_str);
	!ft_strchr("bpdiuoxsDUOXS", fmt->specifier) ? fmt->str = ft_strnew(1) : 0;
	free(copy_str);
}
