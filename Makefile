# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 18:16:10 by smorty            #+#    #+#              #
#    Updated: 2019/05/04 18:22:19 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = srcs/ft_printf.c srcs/parse_format.c srcs/print_formatted.c srcs/print_chars.c srcs/print_numbers.c srcs/ntoa_base.c

OBJ = ${SRC.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ) libft/libft.a
	@ranlib $(NAME)

%.o: %.c
	@gcc $(FLAGS) -c $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)