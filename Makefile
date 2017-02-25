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

NAME = libftprintf.a

G = gcc

FLAG = -Wall -Wextra -Werror

SRC = ft_printf.c \
      specifier_and_modifier.c \
      write_console.c \
      itoa_base.c \
      convert_to_char.c \
      write_specifacator_ox.c \
      write_specifacator_cs.c

HDR = ft_printf.h

OBJ = $(SRC:.c=.o)

DEL = rm -f

all: $(NAME)

$(NAME) : $(OBJ)
		make -C libft
		ar -cru $(NAME) $(OBJ) libft/*.o
		ranlib $(NAME)
		@echo libftprintf.a is ALIVE!!!

%.o: %.c
		$(G) $(CFLAGS) -c -o $@ $<

clean:
		make clean -C ./libft
		$(DEL) $(OBJ)
		@echo OBJ_libftprintf is DEAD!!!

fclean: clean
		make fclean -C ./libft
		$(DEL) $(NAME)
		@echo libftprintf.a is DESTROYED!!!

re: all
		make all -C ./libft
		@echo ALL DAMM FPS is DESTROYED!!!

norm:
		make norm -C ./libft
		norminette $(SRC) $(HDR) | grep -B 1 "Error"

rmsh:
		make rmsh -C ./libft
		rm *~
		rm \#*
		rm *.out