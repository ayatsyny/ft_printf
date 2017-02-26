/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_va.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:58:01 by ayatsyny          #+#    #+#             */
/*   Updated: 2017/02/04 16:47:51 by ayatsyny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#define RED "\x1b[31m"
#define NORM "\x1b[0m"

#define	PTR

//Testing macro - dont change!
#define PRINTF(...){\
	    int ret = 0,ret2 = 0;\
		printf("Origin:\t");ret = printf(__VA_ARGS__);\
	    printf("\tret: %d\n",ret);fflush(stdout);\
	    ft_printf("    Ft:\t");ret2 = ft_printf(__VA_ARGS__);\
	    ft_printf("\t%sret: %d"NORM"\n",(ret == ret2) ? NORM : RED, ret2);\
}
#define TITLE(...){printf("\033[1m\n");printf(__VA_ARGS__);printf("\n\033[0m");}

/*
void var(char *format, ...)
{
		va_list ap;
		char	*test;
		char	*p = format;
			va_start(ap, format);
				if(!strcmp(p, "%d"))
						{
									test  = va_arg (ap, char *);
											printf ("You passed decimal object with value %s\n", test);
												}

					if(!strcmp(format, "%s"))
							{
										char *p = va_arg (ap, char *);
												printf ("You passed c-string \"%s\"\n", p);
													}
						va_end (ap);
}

*/

int main(void)
{
		//var("%d", "548");
		//int a = 10;
		//printf("%.2d\n", -023145);
//		printf("{%03c}", 0);
//		printf("%zu, %zu",	 0, ULLONG_MAX);
//		printf("\n");
//		ft_printf("%zu, %zu", 0, ULLONG_MAX);
//		ft_printf("{%03c}", 0);
	const char A[] = "this is tEEEEst!";
//#ifdef PTR
//	TITLE("Pointer options(field width, presicioin and justification):\n");
//	{
//		char *ptr_c = (char*)malloc(sizeof(char));
//		int ptr_i = 43;
//		long ptr_l = 874748;
//		PRINTF("|%.0p|\t\t|%6p|\t\t|%6.p|\t|%10.6p|", NULL,NULL,NULL,NULL);
//		PRINTF("|%12p||%17p|\t|%-22p|", ptr_c, &ptr_i, &ptr_l);
//		PRINTF("\tOr:\t|%.0p||%6p|\t|%6.p||%.20p|", &ptr_l, &ptr_l, &ptr_l,&ptr_l);
//		free(ptr_c);
//	}
//#endif


//		int nmb = 42;
//		#define CNV "o"
//		printf("\n   |"CNV"|:\n");
//		PRINTF("|%-11-0"CNV"|\t|%-0+11"CNV"|\t|%11+"CNV"|\t|%-11+"CNV"|\t|%0 "CNV"|\t",nmb,nmb,nmb,nmb,nmb);nmb *= -1;
//		PRINTF("|%-11-0"CNV"|\t|%-0+11"CNV"|\t|%11+"CNV"|\t|%-11+"CNV"|\t|%0 "CNV"|",nmb,nmb,nmb,nmb,nmb);nmb *= -1;

//	TITLE("Number options(field width, presicion and -):\n");
	{
//		int nmb = 25;
//		#define CNV "i"
//		printf("\n   |"CNV"|:\n");
//		PRINTF("|%1.1"CNV"|\t\t|%5.1"CNV"|\t\t|%5.3"CNV"|\t\t|%1.5"CNV"|\t",nmb, nmb, nmb, nmb);
//		PRINTF("|%1.1"CNV"|\t\t|%5.1"CNV"|\t\t|%5.3"CNV"|\t\t|%1.5"CNV"|",-nmb, -nmb, -nmb, -nmb);
//		PRINTF("|%07.5"CNV"|", -nmb);
//		PRINTF("|%3.5"CNV"|\t\t|%3.5"CNV"|\t|%07.5"CNV"|\t|%07.5"CNV"|",nmb, -nmb, nmb, -nmb);
//		PRINTF("|%8.5"CNV"|\t|%8.5"CNV"|\t|%08"CNV"|\t|%08"CNV"|",nmb, -nmb, nmb, -nmb);
//		PRINTF("|%-.10"CNV"|\t|%.-10"CNV"|\t|%-15.-10"CNV"|\t|%15.-10"CNV"|",42,42,42,42);
//		PRINTF("|%-12.8.5"CNV"|\t|%12.-8.5"CNV"|\t|%-12.-8.5"CNV"|\t|%-12.-8.-5"CNV"|\t",42,42,42,42);
//		PRINTF("|%7-.5"CNV"|\t|%-7-.5"CNV"|\t|%7.5-"CNV"|\t|%-7.-5-"CNV"|\t", 42,42,42,42);
//		PRINTF("|%12.8.10.6"CNV"|\t|%20.8.-12.6"CNV"|\t|%20.8.12.-6"CNV"||%20.-5.12.3"CNV"|\t|%10.8.12.6-"CNV"|",42,42,42,42,42);
//		PRINTF("|%."CNV" %.0"CNV" %0."CNV" %0.0"CNV"|\t\t|%"CNV" %.2"CNV" %2."CNV" %2.2"CNV"|\t\t\t\t",0,0,0,0,0,0,0,0);

//		PRINTF("|%#.3"CNV"|", 0);
		printf("\nint printf [%d] \n", printf("%.2s is a string", "this"));
		printf("\n");
		printf("\nint ft_printf [%d] \n", ft_printf("%.2s is a string", "this"));

//	PRINTF("|%5h h"CNV"|", SHRT_MIN);

//	printf("\nint printf [%d] \n", printf("% h"));
//	printf("\n");
//	printf("\nint ft_printf [%d] \n", ft_printf("% h"));

//	printf("%s %s %s %s\n", "this", "is", "a", "multi");
//	ft_printf("%s %s %s %s\n", "this", "is", "a", "multi");

//	printf("%5h.10hi\n", SHRT_MIN);
//	ft_printf("%5h.10hi\n", SHRT_MIN);

//		char str1 [11] = "0123345336789";
//		// Набор символов, которые должны входить в искомый сегмент
//		char str2 [10] = "34";
//		// Переменная, в которую будет занесен адрес первой найденной строки
//		char *istr;
//
//		//Поиск строки
//		istr = strstr(str1,str2);
//
//		//Вывод результата поиска на консоль
//		if ( istr == NULL)
//			printf ("Строка не найдена\n");
//		else
//		printf ("Искомая строка начинается с символа %d [%s]\n", istr-str1+1, istr);

//	printf("\nint printf [%d] \n", printf("%5c", 42));
//	printf("\n");
//	printf("\nint ft_printf [%d] \n", ft_printf("%5c", 42));
	}
//	}
//		printf("%p\n", -023);
//		printf("%x\n", -023);
//		printf("%03.2d\n", 1);
//		printf("%d\n", 10);
//		printf("%-d\n", 10);
//		printf("%+d\n", 10);
//		printf("%0d\n", 10);
//		printf("%#d\n", 10);
//		printf("% d\n", 10);
//
//		printf("%2d\n", 100);
//		printf("%-2d\n", 100);
//		printf("%+2d\n", 100);
//		printf("%02d\n", 100);
//		printf("%#2d\n", 100);
//		printf("% 2d\n", 100);
//		printf("%d\n", 10);
//		printf("%0.2d\n", 1);
//		printf("[%m]\n");
//		printf("% + - 10 5 40 d", 5487);
//		printf("[qwer%3Twer]");
//	//	printf([qer%3Twer]");
//		char ss[] = "5554876_ diu dif dd000";
//		//write(1, "\", 1);
//		printf("test itoa [%d]\n", atoi(ss));
//		printf("[% -hlhhd] [% + hlhhd]\n",356, -356);
//		printf("[%010x] [%010x]\n", 123, -123);
//		printf("[% -010x] [% -010x]\n", 123, -123);
//		printf("[%-+010x] [%-+010x]\n", 123, -123);
//		printf("[%+5 .21 .6-0d] [%+5  .6 10 .6-0d]\n", 123, -123);
//		// printf("[%5 .2 .10d] [%5  .2 .10d]\n", 123, -123);
//		// printf("[%- +5 .2  .10d] [%- +5 .2  .10d]\n", 123, -123);
//		// printf("[%-+ 9d] [%-+ 9d]\n", 123, -123);
//		printf("[%5 ll 14 40  020B d]\n");
//		printf("  ==  [%d] \n", printf("00000", a));
////			var("%s %d", "test string", 255);
//		printf("[%  012d] [%d]\n", -255, 126);
//		printf("[%012bhh l d]  [%012d]\n",-255);
//		printf("[%l'jllzd] [%d]\n", -255, 126);
//		printf("[%+-5d] [%+-5++d]\n", 0, -7);
//		printf("[%-+5d] [%-+5d]\n", 0, -7);
//		printf("[%-5d] [%-5d]\n", 0, -7);
//		printf("[%+5d] [%+5d]\n", 0, -7);
//		printf("[% -+5d] [% -+5d]\n", 0, -7);
//		printf("[% +-5d] [% +-5d]\n", 0, -7);
//		printf("[% 12d] [%d]\n", 255, 126);
//		printf("[%-12d] [%d]\n", 255, 126);
//		printf("%%\n");
				return 0;
}
