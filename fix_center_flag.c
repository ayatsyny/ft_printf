/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_center_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:42:11 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 00:42:24 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	clear_flag_in_center_str(t_fmt *fmt, size_t str_len)
{
	if (ft_strchr("xX", fmt->specifier))
	{
		fmt->str[str_len + 1] = '0';
		fmt->str[1] = fmt->specifier;
	}
	else
	{
		fmt->str[0] = fmt->str[0] + fmt->str[str_len];
		fmt->str[str_len] = fmt->str[0] - fmt->str[str_len];
		fmt->str[0] = fmt->str[0] - fmt->str[str_len];
	}
}
