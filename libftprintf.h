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
	unsigned	precision;
	char		modifier;
	char		letter;
	unsigned	res;
}				t_fmt;

// typedef	void	(*t_func)();

# endif
