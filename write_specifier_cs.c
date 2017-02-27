/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_specifier_cs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:31:18 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 00:31:26 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	calc_width_in_cs(t_fmt *fmt)
{
	int		elem;
	char	sing;
	char	*del[2];

	del[0] = NULL;
	del[1] = NULL;
	sing = fmt->flag_first == '0' ^ fmt->precision > 0 ? fmt->flag_first : ' ';
	sing = sing == '0' ? sing : ' ';
	if ((elem = fmt->width - (int)ft_strlen(fmt->str)) > 0)
	{
		del[0] = ft_memset(ft_strnew(elem), sing, elem);
		del[1] = fmt->str;
		if (fmt->flag_first == '-')
			fmt->str = ft_strjoin(fmt->str, del[0]);
		else
			fmt->str = ft_strjoin(del[0], fmt->str);
	}
	ft_memdel((void **)&del);
}

static void	calc_pression_str(t_fmt *fmt)
{
	if (!fmt->precision && ft_strchr("sS", fmt->specifier))
		fmt->str = "\0";
	else if (fmt->precision > 0 && ft_strchr("sS", fmt->specifier))
		fmt->str = ft_strsub(fmt->str, 0, (size_t)fmt->precision);
}

int			write_str(t_fmt *fmt)
{
	int		count;
	char	null;

	null = ft_strchr("cC", fmt->specifier) && fmt->str[0] ? '1' : 0;
	ft_strchr("cC", fmt->specifier) && fmt->width && !fmt->str[0] ?
	fmt->width-- : 0;
	fmt->precision < 0 ? fmt->precision = 0 : calc_pression_str(fmt);
	if (fmt->width > 0)
		calc_width_in_cs(fmt);
	if (!fmt->str ? write(1, "(null)", 6) : 0)
		return (6);
	ft_putstr(fmt->str);
	count = ft_strchr("cC", fmt->specifier) && !null ? write(1, "\0", 1) : 0;
	return ((int)ft_strlen(fmt->str) + count);
}
