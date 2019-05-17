# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 18:16:10 by smorty            #+#    #+#              #
#    Updated: 2019/05/17 16:28:09 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = $(addprefix srcs/,ft_printf.c parse_format.c print_formatted.c \
		print_cs.c process_d.c process_u.c process_o.c process_x.c \
		process_b.c process_f.c process_e.c print_feg.c utility.c \
		libft/ft_atoi.c libft/ft_isdigit.c libft/ft_strlen.c libft/ft_strncpy.c libft/ft_strjoin.c libft/ft_memset.c libft/ft_bzero.c)

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: srcs/%.c
	@gcc -c $<

clean:
	@rm -f srcs/$(OBJ)
	@make clean -C srcs/libft/

fclean: clean
	@rm -f $(NAME)

re: fclean all