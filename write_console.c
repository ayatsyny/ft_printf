//
// Created by Andriy Yatsynyak on 2/5/17.
//

#include "libftprintf.h"

//int create_str(char *str, t_fmt fmt)
//{
//    int str_len;
//    int sing;
//
//    sing = (fmt.flag_first != 127 || fmt.flag_second != 127 || str[0] == '-') ? 1 : 0;
//    str_len = (int)ft_strlen(str);
//    if (fmt.width > str_len && fmt.width > fmt.precision)
//        return (fmt.width);
//    if (fmt.precision >= fmt.width && fmt.precision > str_len &&
//        ft_strchr("xX", fmt.specifier) && fmt.flag_second == '#')
//        return (fmt.precision + 2);
//    if (fmt.precision >= fmt.width && fmt.precision > str_len &&
//        ft_strchr("oO", fmt.specifier))
//        return (fmt.precision + 1);
//    if (fmt.precision >= fmt.width && fmt.precision > str_len)
//        return (fmt.precision + sing);
//    if (str_len > fmt.width && str_len > fmt.precision)
//        return (str_len + sing);
//    return (str_len + sing);
//}

void    write_decimal(t_fmt fmt, void *value)
{
    //char *num;
    int str_l;
    char *str;
    //char t = fmt.specifier;

    fmt.str = ft_itoa_base((int)value, 10);
    //str_l = create_str(num, fmt);
    //str = ft_strnew((size_t)str_l);
    if (fmt.precision != -1)

    if (ft_strchr("-0", fmt.flag_first))
        //write_flags(fmt, str    );

    ///ft_putstr(num);
}


void    calc_flags(t_fmt fmt)
{
	char flag_buff[3];
	char *del;

	ft_strclr(flag_buff);
	if (!(flag_buff[0] = fmt.str[0] == '-' ? '-' : 0))
		flag_buff[0] = ft_strchr("+ ", fmt.flag_second) ? fmt.flag_second : 0;
	else if (fmt.flag_second == '#' && ft_strchr("xX", fmt.specifier))
		ft_strncpy(flag_buff, "OX", sizeof("OX"));
	else if (fmt.flag_second == '#' && ft_strchr("oO", fmt.specifier))
		flag_buff[0] = '0';
	del = fmt.str;
	fmt.str = ft_strjoin(flag_buff, fmt.str);
	free(del);
}


void calc_width(t_fmt fmt)
{
	int elem;
	char sing;
	char *del;
	size_t cnt;

	del = ft_memalloc(2);
	sing = fmt.flag_first == '0' ? fmt.flag_first : ' ';
	cnt = ft_strchr("oO", fmt.specifier) || ft_strchr("+ ", fmt.specifier)
			|| fmt.str[0] == '-' ? 1 : 0;
	if ((elem = fmt.width - (int)ft_strlen(fmt.str)) > 0)
	{
		del[0] = (char)ft_memchr(ft_strnew(elem), sing, elem);
		del[1] = (char) fmt.str;
		if (fmt.flag_first == '-')
			fmt.str = ft_strjoin(fmt.str, (char *)del[0]);
		else
			fmt.str = ft_strjoin((char *)del[0], fmt.str);
		if (sing == '0' && (cnt += ft_strchr("xX", fmt.specifier) ? 1 : 0))
			clear_flag_in_center_str(fmt, ft_strlen((char *)del[0]), cnt);
	}
	ft_memdel((void **) &del);
}


void clear_flag_in_center_str(t_fmt fmt, unsigned skip_len, size_t copy_len)
{
	while (--copy_len >= 0)
	{
		fmt.str[copy_len] = fmt.str[skip_len - copy_len];
		fmt.str[skip_len - copy_len] = '0';
	}
}

void calc_pression(t_fmt fmt)
{
	int sing;
	int elem;
	char *del;

	del = ft_memalloc(3);
	sing = fmt.str[0] == '-' ? 1 : 0;
	elem = fmt.precision + sing - (int)ft_strlen(fmt.str);
    if ((fmt.str[0] == '0' || (sing && fmt.str[1] == '0')) && fmt.precision < 0)
        ft_strclr(fmt.str);
	else if (elem > 0)
	{
		del[0] = (char)ft_memchr(ft_strnew(elem), '0', elem);
		del[1] = (char)fmt.str;
		fmt.str = ft_strjoin((char *)del[0], fmt.str);
	}
	ft_memdel((void **) &del);
}



void    write_width_diD(char *num, char *str, t_fmt fmt, int str_len)
{
    int index;
    char *del;

    index = num[0] == '-'? 1 : 0;
    if (ft_strchr("-0", fmt.flag_first))
        ft_strcpy(num + index, str + index);
//    else
//        del = ft_strjoin();
}

void write_str(void *value, t_fmt fmt)
{
    char *str;

    str = (char *)value;
    write_default(str, fmt, ft_strlen(str));
    ft_putstr(str);
}

//void write_width()
//{
//
//}

//void    write_width_diD(char *str, t_fmt fmt, size_t str_len)
//{
//    char sing;
//    int len;
//    char *del;
//
//    del = NULL;
//    sing = (char) (str[0] == '-' ? 1 : 0);
//    fmt.res += str_len;
//    if ((len = fmt.width - (unsigned) str_len + fmt.res) > 0)
//    {
//        if (fmt.flag_first == '-')
//        {
//            del = (char *) ft_memset(ft_strnew((size_t) len), ' ', (size_t) len);
//            ft_putstr(str + sing);
//            ft_putstr(del);
//        }
//        else if (fmt.flag_first == '0')
//        {
//            del = (char *) ft_memset(ft_strnew((size_t) len), '0', (size_t) len);
//            ft_putstr(del);
//            ft_putstr(str + sing);
//        }
//    }
//    free(del);
//    ft_putstr(str + sing);
//}

//void write_width_with_diD(char *str, t_fmt fmt, size_t str_len)
//{
//    int len;
//    char *del;
//    char tmp;
//    int sing;
//
//    sing = str[0] == '-' ? 1 : 0;
//    if ((len = fmt.width - (unsigned) str_len) > 0 && fmt.precision > str_len - sing)
//    {
//        len = len > 0 ? len : fmt.precision;
//        tmp = (char)(fmt.precision != -1 ? '0' : '/');
//        tmp = (char) (fmt.flag_first == '-' || tmp == '/' ? ' ' : '0');
//        del = (char *) ft_memset(ft_strnew((size_t) len), tmp, (size_t) len);
//        if (ft_strchr("-0", fmt.flag_first))
//        {
//            if (sing)
//                write(1, "-", 1);
//            else if (ft_strchr("+ ", fmt.flag_second) && fmt.flag_first == '-')
//                ft_putchar(fmt.flag_second);
//            ft_memcpy(del + sing, str + sing, str_len - sing);
//            ft_putstr(del);
//        }
//
//        //if (fmt.width > fmt.precision)
//
//
//    }
//}

//void    write_width_with_diD(char *str, t_fmt fmt, size_t str_len) {
//    int len_width;
//    char *del;
//
//    if ((len_width = fmt.width - (unsigned) str_len) > 0)
//    {
//        if (fmt.flag_first == '-')
//        {
//            ft_putstr(str);
//            del = (char *) ft_memset(ft_strnew((size_t) len_width), ' ', (size_t) len_width);
//            ft_putstr(del);
//        } else if (fmt.flag_first == '0')
//        {
//            if (str[0] == '-')
//                write(1, "-", 1);
//            else
//                del = (char *) ft_memset(ft_strnew((size_t) len_width), '0', (size_t) len_width);
//            ft_putstr(del);
//        }
//    } else
//    {
//        if (ft_strchr("+ ", fmt.flag_second))
//            ft_putchar(fmt.flag_second);
//        ft_putstr(str);
//    }
//    free(del);
//}