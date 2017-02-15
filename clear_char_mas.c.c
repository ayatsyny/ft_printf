//
// Created by andriy on 15.02.17.
//

#include "libftprintf.h"

void    init_char_points(char *point, unsigned elem)
{
    unsigned i;

    i = -1;
    while (point[++i])
        point[i] = 0;
}

void    del_char_data(char  *point, unsigned elem)
{
    unsigned i;

    i = -1;
    while (++i < elem)
        free(point[i]);
    free(point);
}