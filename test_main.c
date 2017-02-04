/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 13:45:29 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/01/15 22:21:32 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

/*
void	foo(char *fmt, ...)
{
	va_list ap, ap2;
	int d;
	char c, *s;

	va_start(ap, fmt);
	printf("test %s", fmt);
	va_copy(ap2, ap);
	while (*fmt)
		switch(*fmt++){
			case 's':
				s = va_arg(ap, char *);
				printf("%s\n", s);
				break;
			case 'd':
				d = va_arg(ap, int);
				printf("%d\n", d);
				break;
			case 'c':
				c = va_arg(ap, int);
				printf("%c\n", c);
				break;
		}
	va_end(ap);
	va_end(ap2);
}
*/


int main(void)
{
	printf("TEst base printf \n");
	printf("[%0d]\n", 1234);
	printf("[%d]\n", 1234);
	printf("[%-6d]\n", 1234);
	printf("[%11d]\n", 1234);
	printf("[%s]\n", "test some issue str");
	ft_printf("%d\n", 255);
	printf("%O\n", 259);
	// printf("%s\n", "руский гад");
	ft_printf("%s \a\n", "test string");
	printf("%-s\n", "test string");
	return (0);
}


