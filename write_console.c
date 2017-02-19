//
// Created by Andriy Yatsynyak on 2/5/17.
//

#include "libftprintf.h"
#include <string.h>

static void clear_flag_in_center_str(t_fmt *fmt, size_t str_len)
{
	if (ft_strchr("xX", fmt->specifier))
	{
		fmt->str[str_len + 1] = '0';
		fmt->str[1] = fmt->specifier;
	}
	else
	{
//		tmp = fmt->str[0];
//		fmt->str[0] = fmt->str[str_len];
//		fmt->str[str_len] = tmp;
		fmt->str[0] = fmt->str[0] + fmt->str[str_len];
		fmt->str[str_len] = fmt->str[0] - fmt->str[str_len];
		fmt->str[0] = fmt->str[0] - fmt->str[str_len];
	}
}

int	write_decimal(t_fmt *fmt)
{
	fmt->precision < 0 ? fmt->precision = 0 : calc_pression(fmt);
	if (fmt->str[0] != '-' && (fmt->flag_first != '=' || fmt->flag_second != '='))
		calc_flags(fmt);
	if (fmt->width)
		calc_width(fmt);
    if (fmt->specifier == 'x')
		ft_strlowcase(fmt->str);
	ft_putstr(fmt->str);
	return ((int)ft_strlen(fmt->str));
}

void cal_letter(t_fmt *fmt)
{
	fmt->specifier == 'c' && fmt->width && !fmt->str[0] ? fmt->width-- : 0;
	fmt->precision < 0 ? fmt->precision = 0 : calc_pression_str(fmt);
	if (fmt->flag_first != '=' || fmt->flag_second != '=')
		calc_flags(fmt);
//	if (fmt->specifier == 'c' && fmt->width > 1 && !fmt->str[0])
//		fmt->width--;
	if (fmt->width > 0)
		calc_width(fmt);
}

int	write_str(t_fmt *fmt)
{
	char *del;
	int count;

	del = NULL;
	(!fmt->str && (fmt->specifier == 'c' || (fmt->specifier == 's' &&
			(fmt->str = ft_strdup("(null)"))))) ? del = fmt->str : 0;
	ft_putstr(fmt->str);
	count = fmt->specifier == 'c' && (!fmt->str[0] ^ ft_strequ(fmt->str, " "))
			? write(1, "\0", 1) : 0;
	free(del);
	return ((int)ft_strlen(fmt->str) + count);
}

void    calc_flags(t_fmt *fmt)
{
	char flag_buff[3];
	char *del;

	ft_strclr(flag_buff);
	if (fmt->flag_second == '#' && ft_strchr("xX", fmt->specifier) &&
			!ft_strequ(fmt->str, "0") && fmt->str[0] != '\0')
		ft_strncpy(flag_buff, "0X", 2);
	else if (fmt->flag_second == '#' && ft_strchr("oO", fmt->specifier))
		flag_buff[0] = '0';
	else if (ft_strchr("uU", fmt->specifier))
		return ;
	else if (!(flag_buff[0] = fmt->str[0] == '-' ? '\0' : 0) && !ft_strchr("cs%", fmt->specifier))
		flag_buff[0] = ft_strchr("+ ", fmt->flag_second) ? fmt->flag_second : 0;
	del = fmt->str;
	fmt->str = ft_strjoin(flag_buff, fmt->str);
	if (ft_strchr("puoxXUO", fmt->specifier))
		free(del);
}

void calc_width(t_fmt *fmt)
{
	int elem;
	char sing;
	char *del[2];
	size_t cnt;

	del[0] = NULL;
	del[1] = NULL;
	sing = fmt->flag_first == '0' ^ fmt->precision > 0 ? fmt->flag_first : ' ';
	sing = sing == '0' ? sing : ' ';
	cnt = ft_strchr("+ #", fmt->flag_second) || fmt->str[0] == '-' ? 1 : 0;
	if ((elem = fmt->width - (int)ft_strlen(fmt->str)) > 0)
	{
		del[0] = ft_memset(ft_strnew(elem), sing, elem);
		del[1] = fmt->str;
		if (fmt->flag_first == '-')
			fmt->str = ft_strjoin(fmt->str, del[0]);
		else
		{
			fmt->str = ft_strjoin(del[0], fmt->str);
			if (cnt && fmt->flag_first == '0')
				clear_flag_in_center_str(fmt, ft_strlen(del[0]));
		}
	}
	ft_memdel((void **) &del);
}

void	calc_pression(t_fmt *fmt)
{
	int sing;
	int elem;
	char *del[2];

	del[0] = NULL;
	del[1] = NULL;
	sing = fmt->str[0] == '-' && !ft_strchr("scSC", fmt->specifier) ? 1 : 0;
	elem = (int)(fmt->precision + sing - ft_strlen(fmt->str));
    if (ft_strequ(fmt->str, "0") && !fmt->precision)
        ft_strclr(fmt->str);
	else if (elem > 0)
	{
		del[0] = (char *)ft_memset(ft_strnew(elem), '0', elem);
		del[1] = fmt->str;
		fmt->str = ft_strjoin(del[0], fmt->str);
	}
	if (fmt->str[0] == '-' || ft_strchr(fmt->str, '-'))
		clear_flag_in_center_str(fmt, ft_strlen(del[0]));
	ft_memdel((void **) &del);
}

void 	calc_pression_str(t_fmt *fmt)
{
	if (fmt->precision > 0)
		fmt->str = ft_strsub(fmt->str, 0, (size_t)fmt->precision);
}