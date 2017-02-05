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
    ft_putstr(num);
}