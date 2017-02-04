//
// Created by Andriy Yatsynyak on 2/3/17.
//

void    convert_type(char letter, va_list ap)
{
    if (ft_strchr("dicoOxX", letter))
        return (va_arg(ap, int));
    if (ft_strchr("uU", letter))
        return (va_arg(ap, unsigned));
    if


}