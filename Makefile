# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 18:16:10 by smorty            #+#    #+#              #
#    Updated: 2019/05/28 15:55:29 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCDIR = srcs

SRC = 	$(addprefix $(SRCDIR)/,ft_printf.c parse_params.c process_format.c\
		process_cs.c process_d.c process_u.c process_o.c process_x.c\
		process_b.c process_a.c process_feg.c process_float.c output.c colors.c\
		unicode.c libft/ft_atoi.c libft/ft_strlen.c\
		libft/ft_memset.c libft/ft_bzero.c libft/ft_strnequ.c libft/ft_strcpy.c)

OBJ = ${SRC:.c=.o}

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $@

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -I./includes $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
