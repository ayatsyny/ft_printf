/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:16:44 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 00:23:30 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		process_itoa(intmax_t value, int base, char *s, int *a)
{
	static char value_str[] = "0123456789ABCDEF";

	if (value >= base || value <= -base)
		process_itoa(value / base, base, s, a);
	s[(*a)++] = value_str[ITOA(value % base)];
}

static void		process_itoa2(uintmax_t value, uintmax_t base, char *s, int *a)
{
	static char value_str[] = "0123456789ABCDEF";

	if (value >= base)
		process_itoa2(value / base, base, s, a);
	s[(*a)++] = value_str[value % base];
}

static int		get_base(char letter)
{
	int num;

	num = 0;
	if (ft_strchr("duiDU", letter))
		num = 10;
	else if (ft_strchr("pxX", letter))
		num = 16;
	else if (ft_strchr("oO", letter))
		num = 8;
	return (num);
}

char			*ft_itoa_base(intmax_t value, char base_specifier)
{
	int		i;
	char	*mas;
	int		base;

	i = 0;
	if (!(mas = ft_strnew(35)))
		return (NULL);
	base = get_base(base_specifier);
	if (value < 0 && base == 10)
		mas[i++] = '-';
	if (value < -9223372036854775807)
		process_itoa2((uintmax_t)value, (uintmax_t)base, mas, &i);
	else
		process_itoa(value, base, mas, &i);
	mas[i] = '\0';
	return (mas);
}

char			*ft_itoa_base2(uintmax_t value, char base_specifier)
{
	int		i;
	char	*mas;
	int		base;

	i = 0;
	if (!(mas = ft_strnew(35)))
		return (NULL);
	base = get_base(base_specifier);
	process_itoa2(value, (uintmax_t)base, mas, &i);
	mas[i] = '\0';
	return (mas);
}
