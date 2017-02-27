/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:40:57 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 00:41:53 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*covert_to_char(wchar_t *str)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
		i++;
	if (!(new_str = (char *)malloc((size_t)(i + 1))))
		return (NULL);
	len = i + 1;
	i = -1;
	j = -1;
	while (++i < len)
		new_str[++j] = (char)str[i];
	return (new_str);
}
