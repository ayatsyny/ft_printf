//
// Created by andriy on 15.02.17.
//

#include "libftprintf.h"

void    init_char_points(char *point, unsigned elem)
{
    int i;

    i = -1;
    while (++i < elem)
        point[i] = '\0';
}

void    del_char_data(char  *point, unsigned elem)
{
    unsigned i;

    i = -1;
    while (++i < elem)
        free((void *) point);
    free(point);
}