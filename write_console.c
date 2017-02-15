//
// Created by Andriy Yatsynyak on 2/5/17.
//

#include "libftprintf.h"

static void clear_flag_in_center_str(t_fmt fmt, unsigned skip_len, size_t copy_len)
{
	int len;

	len = (int)copy_len;
	while (--len >= 0)
	{
		fmt.str[copy_len] = fmt.str[skip_len - len];
		fmt.str[skip_len - len] = '0';
	}
}

unsigned	write_decimal(t_fmt *fmt)
{
	calc_pression(fmt);
	calc_flags(fmt);
	calc_width(fmt);
    if (fmt->specifier == 'x')
        ft_fun(fmt->str);
	ft_putstr(fmt->str);
	return ((unsigned)ft_strlen(fmt->str));
}

void    calc_flags(t_fmt *fmt)
{
	char flag_buff[3];
	char *del;

	ft_strclr(flag_buff);
	if (!(flag_buff[0] = fmt->str[0] == '-' ? '-' : 0))
		flag_buff[0] = ft_strchr("+ ", fmt->flag_second) ? fmt->flag_second : 0;
	else if (fmt->flag_second == '#' && ft_strchr("xX", fmt->specifier))
		ft_strncpy(flag_buff, "OX", sizeof("OX"));
	else if (fmt->flag_second == '#' && ft_strchr("oO", fmt->specifier))
		flag_buff[0] = '0';
	del = fmt->str;
	fmt->str = ft_strjoin(flag_buff, fmt->str);
	free(del);
}

void calc_width(t_fmt *fmt)
{
	int elem;
	char sing;
	char *del[2];
	size_t cnt;

	//del = (char *)ft_memalloc(2);
	init_char_points(*del, 2);
	sing = fmt->flag_first == '0' ? fmt->flag_first : ' ';
	cnt = ft_strchr("oO", fmt->specifier) || ft_strchr("+ ", fmt->specifier)
			|| fmt->str[0] == '-' ? 1 : 0;
	if ((elem = fmt->width - (int)ft_strlen(fmt->str)) > 0)
	{
		del[0] = ft_memchr(ft_strnew(elem), sing, elem);
		del[1] = fmt->str;
		if (fmt->flag_first == '-')
			fmt->str = ft_strjoin(fmt->str, del[0]);
		else
			fmt->str = ft_strjoin((char *)del[0], fmt->str);
		if (sing == '0' && (cnt += ft_strchr("xX", fmt->specifier) ? 1 : 0))
			clear_flag_in_center_str(*fmt, ft_strlen(del[0]), cnt);
	}
	del_char_data(*del, 2);
//	ft_memdel((void **) &del);
}

void	calc_pression(t_fmt *fmt)
{
	int sing;
	int elem;
	char *del[3];

	//del = ft_memalloc(3);
	init_char_points(*del, 3);
	sing = fmt->str[0] == '-' ? 1 : 0;
	elem = fmt->precision + sing - (int)ft_strlen(fmt->str);
    if ((fmt->str[0] == '0' || (sing && fmt->str[1] == '0')) && fmt->precision < 0)
        ft_strclr(fmt->str);
	else if (elem > 0)
	{
		del[0] = ft_memchr(ft_strnew(elem), '0', elem);
		del[1] = fmt->str;
		fmt->str = ft_strjoin(del[0], fmt->str);
	}
	del_char_data(*del, 3);
//	ft_memdel((void **) &del);
}