//
// Created by Andriy Yatsynyak on 2/5/17.
//

#include "libftprintf.h"

//void    switsh_write(void * value, t_fmt fmt)
//{
//    if (ft_strchr("oOxX", fmt.specifier))
//
//}


void    write_decimal(void  *value, t_fmt fmt)
{
    char *num;
    char t = fmt.specifier;

    num = ft_itoa((int)value);
    write_default(num, fmt, ft_strlen(num));
    ft_putstr(num);
}

void write_letter(void *value, t_fmt fmt)
{
    char *letter;

    ft_putchar((char)value);
}

void write_str(void *value, t_fmt fmt)
{
    char *str;

    str = (char *)value;
    write_default(str, fmt, ft_strlen(str));
    ft_putstr(str);
}


// !!! maybe add params in func for write_default for count write elements
void write_default(char *value, t_fmt fmt, size_t len_value)
{
    int write_count;
//
    write_count = 0;
//    if (fmt.flag_second == ' ' && value[0] != '-' &&
//            !ft_strchr("cCsS", fmt.specifier))
//    {
//        write_count++;
//        write(1, " ", 1);
//    }
//    else if (fmt.flag_second == '+' && value[0] != '-'
//             && !ft_strchr("cCsS", fmt.specifier))
//    {
//        write_count++;
//        value[0] == '-' ? write(1, "-", 1) : write(1, "+", 1);
//    }
    if (ft_strchr("+ ", fmt.flag_second))
        write_count++;
    if (ft_strchr("-0", fmt.flag_first) && ft_strchr("diD", fmt.specifier))
    {
        write_width_with_diD(value, fmt, len_value + write_count);
    }

}

void write_width_with_diD(char *str, t_fmt fmt, size_t str_len)
{
    int len;
    char *del;
    char tmp;
    int sing;

    sing = str[0] == '-' ? 1 : 0;
    if ((len = fmt.width - (unsigned) str_len) > 0 && fmt.precision > str_len - sing)
    {
        len = len > 0 ? len : fmt.precision;
        tmp = (char)(fmt.precision != -1 ? '0' : fmt.flag_first == '-' ? ' ' : '0');
        del = (char *) ft_memset(ft_strnew((size_t) len), tmp, (size_t) len);
        if (fmt.flag_first == '-')
        {
            if (sing)
                write(1, "-", 1);
            else if (ft_strchr("+ ", fmt.flag_second))
                ft_putchar(fmt.flag_second);
            ft_memcpy(del + sing, str + sing, str_len - sing);
            ft_putstr(del);
        }

        //if (fmt.width > fmt.precision)


    }
}

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