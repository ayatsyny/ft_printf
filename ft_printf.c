/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:26:46 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 00:13:06 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	if (ft_strchr("diuUDoxOXp%cCS", fmt->specifier) && fmt->str)
		del = fmt->str;
	free(del);
	return (*len_writen);
}

int	ft_printf(const char *s, ...)
{
	t_fmt	fmt;
	va_list	ap;
	size_t	i;
	int		read;

	read = 0;
	va_start(ap, s);
	while (*s)
		if (*s == '%' && s++)
		{
			i = 0;
			while (i < ft_strlen(s) && ft_strchr("-+0# hljz123456789.", s[i]))
				i++;
			combination(s, &fmt, i);
			compile_specifier_and_modifier(&ap, &fmt);
			ft_switch(&fmt, &read);
			s += s[i] ? ++i : i;
		}
		else
			read += write(1, s++, 1);
	va_end(ap);
	return (read);
}
