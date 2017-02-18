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
//# define FLAGS "-+0# "    //	!!!! warning priopity very importent
//# define MODIFIER "hljz" //	!!!! warning priopity very importent
# define CONVERSION "pdiuoxcsDUOXCS%"
#include <stdarg.h>
#include <stdint.h>
#include "libft/libft.h"

typedef struct	s_fmt
{
	char			flag_first;
	char			flag_second;
	unsigned		width;
	int	        	precision;
	unsigned char	modifier;
	char			specifier;
    char    		*str;
}				t_fmt;

int			ft_printf(const char *format, ...);
t_fmt		*ft_clear(t_fmt *data);
size_t		combination(char *str, t_fmt *fmt);
char		find_conversion(char *format);
void		find_flags(char *format, t_fmt *data);
int         get_pression(char *format);
int			check_flag_zero(char *format);
unsigned	get_width(char *format);
void		compile_specifier_and_modifier(va_list *ap, t_fmt *fmt);
int			ft_switch(t_fmt *fmt, int *len_writen);
int 		end_format(char	*format, t_fmt *fmt);

char    *ft_itoa_base(intmax_t value, char base_specifier);

/*
 ** write functi ons
 */

/*
**  write decimal functions
*/
int			write_decimal(t_fmt *fmt);
void		calc_pression(t_fmt *fmt);
void    	calc_flags(t_fmt *fmt);
void		calc_width(t_fmt *fmt);

int	write_str(t_fmt *fmt);
void cal_letter(char *c, t_fmt *fmt);

/*
** clear data chars in matrix
*/

void    init_char_points(char *point, unsigned elem);
void    del_char_data(char  *point, unsigned elem);

# endif
