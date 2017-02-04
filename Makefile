# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/15 20:51:56 by ayatsyny          #+#    #+#              #
#    Updated: 2017/01/15 21:23:49 by ayatsyny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

SRC = ft_printf.c \
	  test_main.c

OBJ = $(SRC:.c=.o)
LIB = libftprintf.a

all: $(LIB)

$(LIB): $(OBJ)
	ar -cru $(LIB) $(OBJ)
	ranlib libftprintf.a

%.o %.c libftprintf.h
	gcc $(CFLAGS) -I. -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(LIB)

re fclean all
