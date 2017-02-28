/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_specifier_ox.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:31:44 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 00:35:55 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		costily_for_zero(t_fmt *fmt)
{
	if (fmt->flag_second == '#' && ft_strchr("xX", fmt->specifier))
	{
		if (ft_atoi(fmt->str) == 0)
			return (0);
		else if (fmt->precision_flag)
			return (2);
	}
	if (fmt->flag_second == '#' && ft_strchr("oO", fmt->specifier))
		return (1);
	return (0);
}

static void		calc_flags_int_ox(t_fmt *fmt)
{
	char flag_buff[3];
	char *del;

	ft_strclr(flag_buff);
	if (fmt->flag_second == '#' && ft_strchr("xX", fmt->specifier) &&
			ft_atoi(fmt->str) != 0)
		ft_strncpy(flag_buff, "0X", 2);
	else if (fmt->flag_second == '#' && ft_strchr("oO", fmt->specifier) &&
			(ft_atoi(fmt->str) != 0 || fmt->precision > -1))
		flag_buff[0] = '0';
	del = fmt->str;
	fmt->str = ft_strjoin(flag_buff, fmt->str);
	free(del);
}

static void		calc_width_in_ox(t_fmt *fmt)
{
	int		elem;
	char	sing;
	char	*del[TWO];
	size_t	cnt;

	init_point_str((char **)&del, TWO);
	sing = fmt->flag_first == '0' ^ fmt->precision > 0 ? fmt->flag_first : ' ';
	sing = sing == '0' ? sing : ' ';
	cnt = ft_strchr("+ #", fmt->flag_second) || fmt->str[0] == '-' ? 1 : 0;
	if ((elem = fmt->width - (int)ft_strlen(fmt->str)) > 0)
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

static void		calc_pression_in_ox(t_fmt *fmt, int add_len)
{
	int		elem;
	char	*del[TWO];

	init_point_str((char **)&del, TWO);
	elem = (int)(fmt->precision + GET(fmt->precision) -
			(ft_strlen(fmt->str) + add_len));
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

int				write_num_in_ox(t_fmt *fmt)
{
	fmt->precision > -1 ? calc_pression_in_ox(fmt, costily_for_zero(fmt)) : 0;
	fmt->flag_first != '=' || fmt->flag_second != '=' ?
	calc_flags_int_ox(fmt) : 0;
	fmt->width ? calc_width_in_ox(fmt) : 0;
	fmt->specifier == 'x' ? ft_strlowcase(fmt->str) : 0;
	ft_putstr(fmt->str);
	return ((int)ft_strlen(fmt->str));
}
