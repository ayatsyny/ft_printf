/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:32:45 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/01/24 16:32:36 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# define FLAGS "-+0# "    //	!!!! warning priopity very importent
# define MODIFIER "hljz" //	!!!! warning priopity very importent
# define CONVERSION "pdiuoxcsDUOXCS"
#define FALSE 0
#define TRUE 1
#include <stdarg.h>
#include "libft/libft.h"

enum		e_bool
{
	false = FALSE,
	true = TRUE
}typedef	t_bool;

typedef struct	s_fmt
{
	char		flag_first;
	char		flag_second;
	unsigned	width;
	int	        precision;
	unsigned char	modifier;
	char	specifier;
	unsigned	res;
}				t_fmt;

int		ft_printf(const char *format, ...);
t_fmt	*ft_clear(t_fmt *data);
void    combination(char *str, t_fmt *fmt);
char	find_conversion(char *format);
void	find_flags(char *format, t_fmt *data);
int		find_zero(char *format);
// int		end_format(char	*format, t_fmt *fmt);
unsigned     find_num(char *format);

// char    *find_st_format(char *format, unsigned *read, t_fmt *fmt);
void    *compile_specifier_and_modifier(va_list ap, t_fmt fmt);

char    *ft_itoa_base(int value, int base);

/*
 ** write functions
 */
void    write_flags(char *str, t_fmt *fmt);
void    write_decimal(void  *value, t_fmt fmt);
void    write_default(char *value, t_fmt fmt, size_t len_value);
// void    write_width_diD(char *str, t_fmt fmt, size_t str_len);

//typedef	void	(*t_func)();

# endif
