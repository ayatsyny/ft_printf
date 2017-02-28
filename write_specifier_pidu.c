/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_specifier_pidu.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:36:50 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 00:39:02 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		write_point(t_fmt *fmt)
{
	char *s;

	ft_strlowcase(fmt->str);
	s = fmt->str;
	while (s && *s && *s == ' ')
		write(1, s++, 1);
	ft_putstr("0x");
	ft_putstr(s);
	return ((int)ft_strlen(fmt->str) + 2);
}

static void		calc_flags(t_fmt *fmt)
{
	char flag_buff[2];
	char *del;

	ft_strclr(flag_buff);
	if (ft_strchr("uU", fmt->specifier))
		return ;
	else if (fmt->str[0] != '-' && fmt->specifier != 'p')
		flag_buff[0] = ft_strchr("+ ", fmt->flag_second) ? fmt->flag_second : 0;
	if (flag_buff[0] && fmt->str)
	{
		del = fmt->str;
		fmt->str = ft_strjoin(flag_buff, fmt->str);
		free(del);
	}
}

static void		calc_width(t_fmt *fmt)
{
	int		elem;
	char	sing;
	char	*del[TWO];
	size_t	cnt;

	init_point_str((char **)&del, TWO);
	sing = fmt->flag_first == '0' ? '0' : ' ';
	sing = fmt->precision > -1 ? ' ' : sing;
	cnt = ft_strchr("+ #", fmt->flag_second) || fmt->str[0] == '-' ? 1 : 0;
	if ((elem = fmt->width - (int)ft_strlen(fmt->str) -
						(fmt->specifier == 'p' ? 2 : 0)) > 0)
	{
		del[0] = ft_memset(ft_strnew(elem), sing, elem);
		del[1] = fmt->str;
		if (fmt->flag_first == '-')
			fmt->str = ft_strjoin(fmt->str, del[0]);
		else
		{
			fmt->str = ft_strjoin(del[0], fmt->str);
			if (cnt && fmt->flag_first == '0' && fmt->str[0] != ' ')
				clear_flag_in_center_str(fmt, ft_strlen(del[0]));
		}
	}
	free(del[0]);
	free(del[1]);
}

static void		calc_pression(t_fmt *fmt)
{
	int		elem;
	int		s;
	char	*del[TWO];

	init_point_str((char **)&del, TWO);
	s = fmt->str[0] == '-' ? 1 : 0;
	elem = fmt->precision + GET(fmt->precision) + s - ft_strlen(fmt->str);
	if (ft_strequ(fmt->str, "0") && !fmt->precision)
		ft_strclr(fmt->str);
	else if (elem > 0 && fmt->precision_flag)
	{
		del[0] = (char *)ft_memset(ft_strnew(elem), ' ', elem);
		del[1] = fmt->str;
		fmt->str = ft_strjoin(fmt->str, del[0]);
	}
	else if (elem > 0)
	{
		del[0] = (char *)ft_memset(ft_strnew(elem), '0', elem);
		del[1] = fmt->str;
		fmt->str = ft_strjoin(del[0], fmt->str);
	}
	if (del[0] && ft_strchr(fmt->str, '-'))
		clear_flag_in_center_str(fmt, ft_strlen(del[0]));
	free(del[0]);
	free(del[1]);
}

int				write_decimal(t_fmt *fmt)
{
	fmt->precision > -1 ? calc_pression(fmt) : 0;
	if (fmt->str[0] != '-' && (fmt->flag_first != '=' ||
				fmt->flag_second != '='))
		calc_flags(fmt);
	fmt->width ? calc_width(fmt) : 0;
	if (fmt->specifier == 'p')
		return (write_point(fmt));
	ft_putstr(fmt->str);
	return ((int)ft_strlen(fmt->str));
}
