//
// Created by Andriy Yatsynyak on 2/3/17.
//

#include "libftprintf.h"
#include <stdint.h>
#include <locale.h>
#include <stddef.h>

static void    *convert_specifier(char specifier, va_list ap)
{
    if (ft_strchr("di", specifier))
        return (va_arg(ap, int *));
    if (ft_strchr("uoxX", specifier))
        return (va_arg(ap, unsigned *));
    if ('D' == specifier)
        return (va_arg(ap, long *));
    if (ft_strchr("UO", specifier))
        return (va_arg(ap, unsigned long *));
    if ('c' == specifier)
        return (va_arg(ap, unsigned char *));
    if ('s' == specifier)
        return (va_arg(ap, char *));
    return (NULL);
}

static void    *convert_modifier_decimal(unsigned char modifier, void *value)
{
    if (modifier == 'h' << 1)
        return ((signed char *)value);
    if (modifier == 'h')
        return ((short *)value);
    if (modifier == 'l')
        return ((long *)value);
    if (modifier == 'l' << 1)
        return ((long long *)value);
    if (modifier == 'j')
        return ((intmax_t *)value);
    if (modifier == 'z')
        return ((size_t *)value);
    return (value);
}

static void    *convert_modifier_others(unsigned char modifier, void * value, char specifier)
{
//    if (specifier == 'c' && modifier == 'l')
//        return ((wint_t)value);
    if (specifier == 's' && modifier == 'l')
        return ((wchar_t *)value);
    if (modifier == 'h' * 2)
        return ((unsigned char *)value);
    if (modifier == 'h')
        return ((unsigned short *)value);
    if (modifier == 'l')
        return ((unsigned long *)value);
    if (modifier == 'l' * 2)
        return ((unsigned long long *)value);
    if (modifier == 'j')
        return ((uintmax_t *)value);
    if (modifier == 'z')
        return ((size_t *)value);
    return (value);
}

void    *compile_specifier_and_modifier(va_list ap, t_fmt fmt)
{
    void *value;

    value = NULL;
    if (!(value = convert_specifier(fmt.specifier, ap)))
        return (NULL);
    if (ft_strchr("di", fmt.specifier) && fmt.modifier != '=')
        return (convert_modifier_decimal(fmt.modifier, value));
    else if (ft_strchr("uoxXDUOcs", fmt.specifier) && fmt.modifier != '=')
        return (convert_modifier_others(fmt.modifier, value, fmt.specifier));
    return (value);
}