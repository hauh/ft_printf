/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:08:11 by smorty            #+#    #+#             */
/*   Updated: 2019/05/02 22:51:20 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define S_NUM(c) (c == 'd' || c == 'i' || c == 'u')
# define S_816(c) (c == 'o' || c == 'x' || c == 'X')
# define S_REA(c) (c == 'f' || c == 'F' || c == 'e' || c == 'E')
# define S_CHA(c) (c == 'c'	|| c == 's' || c == 'S')
# define S_MSC(c) (c == 'p' || c == 'n')
# define SPEC(c) (S_NUM(c) || S_816(c) || S_REA(c) || S_CHA(c) || S_MSC(c))
# define FLAG(c) (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')

enum			e_modifiers
{
	NO, HH, H, L, LL
};

typedef struct	s_formatted
{
	enum e_modifiers	mod;
	short				minus;
	short				plus;
	short				space;
	short				hash;
	short				zero;
	int					percision;
	int					width;
	char				spec;
}				t_formatted;

void			initialize_struct(t_formatted *to_print);
void			store_flag(const char **format, t_formatted *to_print);
void			store_mod(const char **format, t_formatted *to_print);
void			store_width(const char **format, t_formatted *to_print);
void			store_percision(const char **format, t_formatted *to_print);
int				print_number(t_formatted to_print, void *argp);
int				print_ints(long long n, t_formatted to_print);

#endif
