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

void	error_exit(char	*str)
{
	ft_putendl(str);		//	debug information
	write(1, "error\n", 6);
	exit(1);
}

int	in_str(char	*dst, char *str)
{
	unsigned int i;
	unsigned int j;

	j = -1;
	while(dst[++j])
	{
		i = 0;
		while (str[i] && dst[j] != str[i])
			i++;
		if (i < strlen(str))
			return (i);
	}
	return (-1);
}

//int	index(char *str, char letter)
//{
//	int i;
//
//	i = -1;
//	while (str[i] && str[i] != letter)
//		i++;
//	if (i < strlen(str))
//		return (i);
//	return (-1);
//}

//
//t_func	ft_switch(char	conversion, void  *value)
//{
//    static t_func	funcs[6];
//    int				funcs_index;
//
//    funcs[1] = &;
//    funcs[2] = &;
//    funcs[3] = &;
//    funcs[4] = &;
//    funcs[5] = &;
//    funcs[6] = &;
//    if (conversion == 'p')
//        return (funcs[1]);
//    else if (ft_strchr("diuUD", conversion))
//        return (funcs[2]);
//    else if (ft_strchr("oxOX", conversion))
//        return (funcs[3]);
//}

void ft_switch(t_fmt fmt, void * value)
{
    if (fmt.specifier == 'p')
        return ;
    else if (ft_strchr("diuUD", fmt.specifier))
        write_decimal(value, fmt);
    else if (ft_strchr("oxOX", fmt.specifier))
        return ;
}

//
//int	find_num(char *format)
//{
//	size_t	len;
//	size_t	f_end;
//
//	len = strlen(format);
//	while (--len > 0)
//		if (isdigit(format[len]))
//		{
//			f_end = len--;
//			while (isdigit(format[len]))
//				len--;
//			if (len <= f_end && format[f_end] != '0')
//				return (atoi(format + len));
//		}
//	return (-1);
//}

//while (len > 0 && !ft_isdigit(format[len]))
//len--;
//f_end = len;
//while (--len > 0 && ft_isdigit(format[len]))
//;
//if (len <= f_end && format[f_end - len] != '0')
//num = ft_strsub(format, len, f_end);
//if (num)
//number = atoi(num);
//free(num);
//return ((unsigned)number);


// version 1.2
unsigned     find_num(char *format)
{
    size_t len;
    size_t f_end;
    char *num;
    int number;

    num = NULL;
    number = -1;
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

//int		find_width(char *format, int *mas)
//{
//	size_t len;
//
//	len = strlen(format);
//	while (--len < 0)
//
//}

int		end_format(char	*format)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;
    size_t len = strlen(CONVERSION);        // maybe change somethings for default
	char end_letter[] = "bkmtwyBKMTWY{|}~[]()@?>=</&!";

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
            if (end_letter[j] == format[i] || CONVERSION[k] == format[i])
//            {
//                printf("end lettert %c index %u\n", format[i], i);
                return (i);
//            }
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
		if (strrchr(format, '-'))
			data->flag_first = '-';
		//	mas[0] = '-';
		else if (data->flag_first == 0  && find_zero(format)) //!!!warning don't corect!!!
			data->flag_first = '0';
//			mas[0] = '0';
		//if (str_in(flag_conversion, "oxOX") && strrchr(format, '#'))
		//	data->flag_second = '#';
			//mas[1] = '#';
		if (data->flag_second != '0' && strrchr(format, '+'))
			data->flag_second = '+';
		//	mas[1] = '+';
		else if (data->flag_second != '0' && strrchr(format, ' '))
			data->flag_second = ' ';
			// nas[1] = ' ';
}


//int		find_conversion(char *format)
//{
//	static int count[6] = {2, 1, 1, 2, 1, 1};
//	char str[3];
//	size_t len = strlen(MODIFIER) + 2; // becouse we have hh, ll
//	int	i;
//	int j;
//
//	i = -1;
//	j = 0;
//    str[2] = '\0';
//	while (++i < len)
//	{
//		str[0] = MODIFIER[j];
//		str[1] = '\0';
//		if (count[i] > 1)
//			str[1] = MODIFIER[j];
//        printf("test format [%s]\n", format);
//        printf("test str [%s]\n", str);
//		if (!strstr(format, str))
//			j++;
//		else
//			return (MODIFIER[j] * 2);
//	}
//	return (-1);
//}

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


//void	validatiion(int *array, char *str)
//{
//	array[0] = in_str(FLAGS, str);
//	if (array[0] != -1)
//		array[1] = index(FLAGS, '+');
//	array[2] = // todo create validation for digital number in printf
//	array[5] = in_str(CONVERSION, str);
//
//
//}
/*
char	*find_st_format(char *format, unsigned int read)
{
	char *p_format;
	char *begin_format;
	unsigned int i;

	p_format = format;
	while ((begin_format = strchr(format, '%')) && *begin_format && *(begin_format + 1) == '%')
		format = begin_format;
	if (!*begin_format)
		write(1, p_format, (read = sizeof(p_format)));
	else if (*p_format != *begin_format)
		write(1, p_format, (read = sizeof(p_format - strlen(begin_format))));
	if (*begin_format)
		//format = in_str(CONVERSION, begin_format) +  begin_format; fix for this
	return (strndup(begin_format, i));
}
*/

/*
// new version 1.1
char	*find_st_format(char *format, unsigned int read)
{
	char *p_format;
	char *begin_format;
	char *end_format;
	unsigned int i;

	p_format = format;
	while ((begin_format = strchr(format, '%')) && *begin_format && *(begin_format + 1) == '%')
		format = begin_format;
	end_format = begin_format;
	while ((end_format = strchr(format, '%')) && *end_format && *(end_format + 1) == '%')
		format = end_format;
	if (!*begin_format)
		write(1, p_format, (read = sizeof(p_format)));
	else if (*p_format != *begin_format)
		write(1, p_format, (read = sizeof(p_format - strlen(begin_format))));
	if (*end_format)
		return (strndup(begin_format, sizeof(end_format)));
	return (strndup(begin_format, sizeof(begin_format)));
}
*/

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

// important use to ft_strsub -- strndup
// new version 1.2
char	*find_st_format(char **format, unsigned int *read)
{
	char	*p_format;
	char	*begin_format;
	int		end_fmt;
    char    *test; // test

	p_format = *format;
	while ((begin_format = ft_strchr(*format, '%')))
    {
        if (*(begin_format + 1) == '%')
            continue;
        *format = begin_format + 1;
        if (*begin_format)
            break ;
    }
	if (!begin_format || *(begin_format + 1) == '%')
	{
        write(1, p_format, (*read += strlen(*format)));
        return (NULL);                                      //
	}
	else
        end_fmt = end_format(begin_format + 1);             //  miss sign '%'
    write(1, p_format, (*read += strlen(p_format) - strlen(begin_format)));
	if (end_fmt != -1)
    {
            *format = *format + strlen(begin_format);
        test = test_strsub(begin_format + 1, 0, (size_t)end_fmt);
        return (test);
//        return (ft_strsub(begin_format, 0, (size_t)end_format));
    }
	return (strndup(begin_format, strlen(begin_format)));
}

//char    *find_st_format2(char *format, unsigned int *read)
//{
//    char    *p_format;
//    char    *begin_format;
//    int     end_fmt;
//
//    p_format = format;
//    while ((begin_format = strchr(format, '%')) && *(begin_format + 1) == '%')
//        format = begin_format + 1;
//
//}




//void validation(int *array, char *str)
//{
//	array[0] = in_str(FLAGS, str);
//	if (array[0] != -1)
//		array[-1] = index(FLAGS, '+');
//}

// old version
/*
int		ft_printf(const char format, ...)
{
	// mas it's inforamtion conversion specifications
	// mas[0] - flags "#0-+ " || FLAGS
	// if format == '+' && format == '-' (position not importent) 
	// mas[1] - save '-'
	// mas[2] - minimum field width
	// mas[3] - precision
	// mas[4] - size modifier "h, l, j, z, hh, ll" || MODIFIER
	// mas[5] - conversion letter "p, d, i, u, o, x, c, s, D, U, O, X, C, S" || CONVERSION
	// mas[6] - result read letters in ft_printf
	int mas[7];
	int	i;
	va_list	argv;
	unsigned int	read;
	char 	*p_format;

	i = -1;
	p_format = format;
	va_start(argv, p_format);
	while (*p_format)
	{
		while (mas[++i] < 6)
			mas[i] = -1;
		validatiion(mas, find_st_format(p_format, &read));
	}
	va_end(argv);
	return ;
}
*/

t_fmt	clear(t_fmt *data)
{
	data->flag_first = 0;
	data->flag_second = 0;
	data->width = 0;
	data->precision = 0;
	data->modifier = 0;
	data->specifier = 0;
	data->res = 0;
	return (*data);
}

// new version
int		ft_printf(const char *format, ...)
{
	t_fmt	fmt;
	va_list	argv;
	unsigned read;
	char	*p_format;
    char    *f_format;

	// read = 0;vim Make
	p_format = (char *)format;
    f_format = strdup(format);
	va_start(argv, format);
	while (f_format && p_format)
	{
		read = 0;
        clear(&fmt);
        if (!(p_format = find_st_format(&f_format, &read)))
            continue ;
//        printf("test [%s]\n", f_format);
		fmt.specifier = p_format[strlen(p_format) - 1];
		find_flags(p_format,  &fmt);
		fmt.width = find_num(p_format);
//		fmt.precision = find_num(strchr(p_format, '.') + 1);
		fmt.modifier = find_conversion(p_format);
        ft_switch(fmt, compile_specifier_and_modifier(argv, fmt));

	}
	va_end(argv);
	return (read);
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