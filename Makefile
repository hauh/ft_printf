# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 18:16:10 by smorty            #+#    #+#              #
#    Updated: 2019/05/15 17:24:35 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = $(addprefix srcs/,ft_printf.c parse_format.c print_formatted.c print_cs.c print_d.c print_u.c print_o.c print_x.c print_b.c print_f.c print_f.c print_e.c print_feg.c utility.c libft/ft_atoi.c libft/ft_isdigit.c libft/ft_strlen.c libft/ft_strncpy.c libft/ft_strjoin.c libft/ft_memset.c)

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: srcs/%.c
	@gcc -c $<

clean:
	@rm -f srcs/$(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all