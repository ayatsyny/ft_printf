/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_letters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:40:23 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 00:40:32 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned	count_letters(char const *s, char c)
{
	int			i;
	unsigned	count;

	i = -1;
	count = 0;
	while (s && s[++i])
		if (s[i] == c)
			count++;
	return (count);
}
