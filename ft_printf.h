/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 20:05:54 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/27 20:06:01 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define GET(x) (x < 0 ? 1 : 0)
# define ITOA(x) x < 0 ? -x : x
# define TWO 2
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"
# include <stdarg.h>
# include <ctype.h>
# include <stdint.h>
# include "libft/libft.h"

typedef struct	s_fmt
{
	char			flag_first;
	char			flag_second;
	unsigned		width;
	int				precision;
	unsigned char	modifier;
	char			specifier;
	char			precision_flag;
	char			*str;
}				t_fmt;

/*
**  initialization struct
*/

t_fmt			*init_s_fmt(t_fmt *data);

/*
**  ft_printf
*/

int				ft_printf(const char *format, ...);

/*
**  parser
*/

void			combination(const char *str, t_fmt *fmt, size_t index);
unsigned char	get_modifier(char *format);
void			find_flags(char *format, t_fmt *data);
int				get_pression(char *format, t_fmt *fmt);
unsigned		get_width(char *format, unsigned num);
void			compile_specifier_and_modifier(va_list *ap, t_fmt *fmt);

/*
**  choice specifier write
*/

int				ft_switch(t_fmt *fmt, int *len_writen);

/*
**  convert numbers in others system
*/

char			*ft_itoa_base(intmax_t value, char base_specifier);
char			*ft_itoa_base2(uintmax_t value, char base_specifier);

/*
**  write decimal functions int, unsigned, point
*/

int				write_decimal(t_fmt *fmt);

/*
**  write str and letter functions
*/

int				write_str(t_fmt *fmt);

/*
**  write numbers 8 and 16 calculus functions
*/

int				write_num_in_ox(t_fmt *fmt);

/*
**  helper functions for ft_printf
*/

int				check_flag_zero(char *format);
char			*covert_to_char(wchar_t *str);
unsigned		count_letters(char const *s, char c);
void			clear_flag_in_center_str(t_fmt *fmt, size_t str_len);
void			init_point_str(char **str, int len);

#endif
