//
// Created by Andriy Yatsynyak on 2/3/17.
//

#include "libftprintf.h"
#include <stdint.h>

void    *convert_specifier(char specifier, va_list ap)
{
    if (ft_strchr("di", specifier))
        return (va_arg(ap, int));
    if (ft_strchr("uoxX", specifier))
        return (va_arg(ap, unsigned));
    if (ft_strchr("D", specifier))
        return (va_arg(ap, long));
    if (ft_strchr("UO", specifier))
        return (va_arg(ap, unsigned long));
    if (ft_strchr("c", specifier))
        return (va_arg(ap, unsigned char));
    if (ft_strchr("s", specifier))
        return (va_arg(ap, char *));
}

void    *convert_modifier_decimal(char modifier, void *value)
{
    if (modifier == 'h' * 2)
        return ((signed char)value);
    if (modifier == 'h')
        return ((short)value);
    if (modifier == 'l')
        return ((long)value);
    if (modifier == 'l' * 2)
        return ((long long)value);
    if (modifier == 'j')
        return ((intmax_t)value);
    if (modifier == 'z')
        return ((size_t)value);
    return (value);
}

void    *convert_modifier_others(char modifier, void * value, char specifier)
{
    if (specifier == 'c' && modifier == 'l')
        return ((wint_t)value);
    if (specifier == 's' && modifier == 'l')
        return ((wchar_t*)value);
    if (modifier == 'h' * 2)
        return ((unsigned char)value);
    if (modifier == 'h')
        return ((unsigned short)value);
    if (modifier == 'l')
        return ((unsigned long)value);
    if (modifier == 'l' * 2)
        return ((unsigned long long)value);
    if (modifier == 'j')
        return ((uintmax_t)value);
    if (modifier == 'z')
        return ((size_t)value);
    return (value);
}