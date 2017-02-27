/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag_zero.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:42:45 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 00:43:10 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_flag_zero(char *format)
{
	int i;

	i = -1;
	while (format[++i])
	{
		if (format[i] == '0')
			return (1);
		while (ft_strchr(".123456789", format[i]))
			i++;
	}
	return (0);
}
