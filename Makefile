# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smorty <smorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/04 18:16:10 by smorty            #+#    #+#              #
#    Updated: 2019/08/07 21:42:34 by smorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCDIR = srcs

SRC = 	$(addprefix $(SRCDIR)/,ft_printf.c parse_params.c process_format.c\
		process_cs.c unicode.c process_d.c process_u.c process_o.c\
		process_x.c process_b.c process_float.c float_arithmethic.c process_a.c\
		process_efg.c process_efg_2.c output.c colors.c libft/ft_atoi.c\
		libft/ft_strlen.c libft/ft_memset.c libft/ft_bzero.c libft/ft_strnequ.c)

OBJ = ${SRC:.c=.o}

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $@ $(OBJ)
	@printf "\r\e[Jar \e[32m$(notdir $@)\e[0m"
	@ranlib $@
	@printf "\r\e[Jranlib \e[32m$(notdir $@)\e[0m"
	@printf "\r\e[J\e[32m$(notdir $@)\e[0m done!\n\e[?25h"

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -I./includes $(CFLAGS) -c -o $@ $<
	@printf "\r\e[?25l\e[Jcompiling \e[32m$(notdir $^)\e[0m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
