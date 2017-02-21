//
// Created by Andriy Yatsynyak on 2/21/17.
//

#include "libftprintf.h"

char *covert_to_char(wchar_t *str)
{
	long	i;
	char	*new_str;
	long 	len;
	int		j;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (!(new_str = (char *)malloc(i + 1)))
		return (NULL);
	len = i + 1;
	i = -1;
	j = -1;
	while (++i < len)
		new_str[++j] = (char)str[i];
	return (new_str);
}