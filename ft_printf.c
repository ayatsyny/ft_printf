/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:26:46 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/01/24 16:32:29 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void ft_switch(t_fmt *fmt, void *value)
{
    if (ft_strchr("diuUDoxOXp", fmt->specifier))
        write_decimal(*fmt, value);
    else if (ft_strchr("cC", fmt->specifier))
        return ;
    else if (ft_strchr("sS", fmt->specifier))
        return ;

}

unsigned     find_num(char *format)
{
    size_t len;
    size_t f_end;
    char *num;
    int number;

    num = NULL;
    number = 0;
    if (!format)
        return (0);
    len = ft_strlen(format) - 1;
    while (--len > 0)
        if (ft_isdigit(format[len]))
        {
            f_end = len--;
            while (len > 0 && isdigit(format[len]))
                 len--;
            if (len < f_end && format[f_end - len] != '0')
            {
                num = ft_strsub(format, (unsigned)(len + 1), f_end - len);
                break ;
            }
        }
    if (num)
        number = atoi(num);
    free(num);
    return ((unsigned)number);
}

int		end_format(char	*format, t_fmt *fmt)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;
    size_t len = ft_strlen(CONVERSION);        // maybe change somethings for default
	unsigned char end_letter[] = "bkmtwyBKMTWY{|}~[]()@?>=</&!";
//    size_t len_end_letter = strlen(end_letter);
	// char skip[] = "qv_,:;";
	// n - bus error (flag in pdfs-bonus)
	// q - deprecated (you dont use this flag pds not inf about create functionals)
	// original function skip for this (flag q)
	// v - repeat in 16 overload (read man )
	//	a b c d e f g h i j k l m n o p q r s t u v w x y z
	i = -1;
	while (format[++i])
	{
		k = -1;
        j = -1;
		while (end_letter[++j])
        {
            if (++k == len)
            {
                j -= 1;
                k = -1;
                continue ;
            }
            if (CONVERSION[k] == format[i])
            {
                fmt->specifier = (unsigned char) CONVERSION[k];
                return (i + 1);
            }
            if (end_letter[j] == format[i])
            {
                fmt->specifier = end_letter[j];
                return (-1);
            }
        }
//		while(end_letter[j] && end_letter[j] != format[i])
//			j++;
//		if (j < strlen(end_letter))
//			return ((int)i);
//		while(CONVERSION[k] && CONVERSION[k] != format[i])
//			k++;
//		if (k < strlen(CONVERSION))
//			return (int(i));
	}
	return (-1);
}

int		find_zero(char *format)
{
	int i;
	int res;
	int f;

	i = -1;
	f = 0;
	while (format[++i])
	{
		res = isdigit(format[i]);
		if (res != 0)
		{
			if (res != '0' && !f)
				f = 1;
			else if (res == '0' && !f)
				return (1);
			else if (res == 0)
				f = 0;
		}
	}
	return (0);
}


void	find_flags(char *format, t_fmt *data)
{
    if (strchr(format, '-'))
        data->flag_first = '-';
    else if (find_zero(format))
        data->flag_first = '0';
    //	mas[0] = '-';
//		if (data->flag_first == 0  && find_zero(format)) //!!!warning don't corect!!!
//			data->flag_first = '0';
//			mas[0] = '0';
    //if (str_in(flag_conversion, "oxOX") && strrchr(format, '#'))
    //	data->flag_second = '#';
        //mas[1] = '#';

    //	mas[1] = '+';
    if (strchr(format, '+'))
        data->flag_second = '+';
    else if (strchr(format, ' '))
        data->flag_second = ' ';
    if (ft_strchr(format, '#') && ft_strchr("oOxX", data->specifier))
        data->flag_second = '#';
			// nas[1] = ' ';
}

// version 1.2
char		find_conversion(char *format)
{
    static char *conversion[] = {"hh", "h", "l", "ll", "j", "z"};
    int i;

    i = -1;
    while (++i < 6)
        if (strstr(format, conversion[i]))
        {
            if (i == 0 || i == 3)
                return ((unsigned char)(conversion[i][0] << 1));
            else
                return (conversion[i][0]);
        }
    return (0);
}




// todo you need change libft fot ft_strsub
char	*test_strsub(char	const *s, unsigned int start, size_t len)
{
    char	*fresh;
    size_t	i;

    i = 0;
    if (!s || start > (unsigned)len || (size_t)start > ft_strlen(s)
        || (int)start <= -1)
        return (NULL);
    fresh = (char *)malloc(len + 1);
    if (!fresh)
        return (NULL);
    s += start;
    while (s && i < len)
        fresh[i++] = *(char *)s++;
    fresh[i] = '\0';
    return (fresh);
}

t_fmt *ft_clear(t_fmt *data)
{
	data->flag_first = '=';
	data->flag_second = '=';
	data->width = 0;
	data->precision = -1;
	data->modifier = '=';
	data->specifier = '=';
	data->res = 0;
	return (data);
}

int     ft_printf(const char *format, ...)
{
    t_fmt       *fmt;
    va_list     argv;
    unsigned    read;
    int         i;

    read = 0;
    i = 0;
    va_start(argv, format);
    while (*format)
    {
        if (*format == '%' && format++)
        {
            i = 0;
            while (i < ft_strlen(format) && !ft_strchr("0123456789hljz-+0# ", format[i]))
                i++;
            ft_switch(fmt, combination(ft_strncpy(ft_strnew(i - 1), format, i - 1), fmt, argv));
            format += (format[i]) ? i + 1 : i;
        }
        else
            ft_putchar(format[i++]);
    }
    return (10);

}

void *combination(char *str, t_fmt *fmt, va_list p)
{
    char *del;
    int len;

    del = str;
    len = (int)ft_strlen(str);
    ft_clear(fmt);
    fmt->specifier = (char) (ft_strchr(CONVERSION, str[len - 1]) ? str[len - 1] : 127);
    find_flags(del,  fmt);
    fmt->width = find_num(del);
//		fmt.precision = find_num(strchr(p_format, '.') + 1);
    fmt->modifier = (unsigned char)find_conversion(del);
    free(del);
    return (fmt->specifier != 127 ? compile_specifier_and_modifier(p, *fmt) : 0);
}


/*
int main(void)
{
//	int y;
//	int x = 0;
//	y = x == 0 ? 1 : 0;
//	int mas[5];
//	for(int i = 0; i < 5; i++)
//		printf("test  [%d]\n", mas[i] = -1);

//	printf("test_origin %d\n", 5);
//	ft_printf("my_print %d\n", 5);
//	printf("x= %d, y= %d \n", x, y);
//	printf("test strchr[%s]\n", strchr("dsfdsf fg  %% dff  dgg \%\%", '%'));
//	printf("[%s]\n", MODIFIER);
//	printf("[%s]\n", CONVERSION);
//	printf("[%d]", printf("dfgdfs  fgfgn  [%d]\n", 55));

    char *s = "wqweq rerw er";
    char *s_proc = "... % - + 40 51 lh d";
    char *s_proc_doub = "%%%";
    char *s_def = "% +-12hhd";
    char *s_mix = "kjflk oiej % +- 4 6 z d reoroeu % -12s";
    char *s_def_l = "%+12d%+- 5s";
    unsigned int read = 0;

//    write(1, "\n", 1);
////    find_st_format(s, &read);
//    //printf("test data \n [%s]\n", s);
//    printf("read [%u] str\n[%s]\n", read, s);
//    printf("my function: \n");
//    ft_printf(s);

    read = 0;
    write(1, "\n", 1);
    //find_st_format(s_def, &read);
    //printf("test data \n [%s]\n", s_def);
    printf("read [%u] str\n[%s]\n", read, s_def);
    printf("my function: \n");
    ft_printf(s_def);

//    read = 0;
//    write(1, "\n", 1);
//    //find_st_format(s_proc, &read);
//    //printf("test data \n [%s]\n", s_proc);
//    printf("read [%u] str\n[%s]\n", read, s_proc);
//    printf("my function: \n");
//    ft_printf(s_proc);
//
//    read = 0;
//    write(1, "\n", 1);
////    find_st_format(s_proc_doub, &read);
//    //printf("test data \n [%s]\n", s_proc_doub);
//    printf("read [%u] str\n[%s]\n", read, s_proc_doub);
//    printf("my function: \n");
//    ft_printf(s_proc_doub);
//
//
//    read = 0;
//    write(1, "\n", 1);
////    find_st_format(s_mix, &read);
//    //printf("test data \n [%s]\n", s_mix);
//    printf("read [%u] str\n[%s]\n", read, s_mix);
//    printf("my function: \n");
//    ft_printf(s_mix);
//
//    read = 0;
//    write(1, "\n", 1);
////    find_st_format(s_def_l, &read);
//    //printf("test data \n [%s]\n", s_def_l);
//    printf("read [%u] str\n[%s]\n", read, s_def_l);
//    printf("my function: \n");
//    ft_printf(s_def_l);

    //char array[] = "string";
    //const char *сii = array;

    //cii = array;
    //func_test(cii);
    //printf("\n\n test const char %c\n", *cii);
	// printf("ldfldkfh \n");
	return (0);
}
*/