# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayatsyny <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/15 20:51:56 by ayatsyny          #+#    #+#              #
#    Updated: 2017/02/05 16:44:54 by ayatsyny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

SRC = ft_printf.c

OBJ = $(SRC:.c=.o)
LIB = libftprintf.a

TARGET = test

all: $(LIB)

$(LIB): $(OBJ)
	make -C libft
	ar -cru $(LIB) $(OBJ) libft/*.o
	ranlib $(LIB)
	@echo libftprintf.a is ALIVE!!!

    %.o: %.c
	    gcc $(CFLAGS) -I. -c -o $@ $<

clean:
	make clean -C ./libft
	rm -f $(OBJ)
	@echo OBJ_libftprintf is DEAD!!!

fclean: clean
	make fclean -C ./libft
	rm -f $(LIB)
	@echo libftprintf.a is DESTROYED!!!

re: fclean all
	@echo ALL DAMP FPS is DESTROYED!!!

$(TARGET):
	gcc -c $(TARGET).c
	gcc -o $(TARGET) $(TARGET).o ft_printf.o -I. $(LIB)

rmsh:
	rm $(TARGET).o $(TARGET)