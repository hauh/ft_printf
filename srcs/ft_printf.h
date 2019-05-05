/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:08:11 by smorty            #+#    #+#             */
/*   Updated: 2019/05/05 23:19:21 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdint.h>

# define S_NUM(c) (c == 'd' || c == 'i' || c == 'u')
# define S_816(c) (c == 'o' || c == 'x' || c == 'X')
# define S_REA(c) (c == 'f' || c == 'F' || c == 'e' || c == 'E')
# define S_CHA(c) (c == 'c'	|| c == 's' || c == 'S')
# define S_MSC(c) (c == 'p' || c == 'n')
# define SPEC(c) (S_NUM(c) || S_816(c) || S_REA(c) || S_CHA(c) || S_MSC(c))
# define FLAG(c) (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')


enum			e_modifiers
{
	NO, HH, H, L, LL, J
};

typedef struct	s_frmt
{
	enum e_modifiers	mod;
	char				minus;
	char				plus;
	char				space;
	char				hash;
	char				zero;
	int					precision;
	int					width;
	char				spec;
}				t_frmt;

int				parse_format(const char **format, va_list argp);
int				print_formatted(va_list argp, t_frmt params);
int				print_integer(intmax_t n, t_frmt params);
int				print_unsigned_base(uintmax_t n, t_frmt params, char base);
int				print_char(const char c, t_frmt params);
int				print_string(const char *s, t_frmt params);
int				find_max(int a, int b, int c);
char			prefix_di(char *s, intmax_t n, t_frmt params);
char			prefix_uox(char *s, uintmax_t n, t_frmt params);

#endif
