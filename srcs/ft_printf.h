/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:08:11 by smorty            #+#    #+#             */
/*   Updated: 2019/05/09 22:51:02 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <wchar.h>

# define S_INT(c) (c == 'i' || c == 'd' || c == 'D' || c == 'u' || c == 'U')
# define S_816(c) (c == 'o' || c == 'O' || c == 'x' || c == 'X')
# define S_REA(c) (c == 'f' || c == 'F' || c == 'e' || c == 'E')
# define S_CHA(c) (c == 'c'	|| c == 's' || c == 'S' || c == 'C')
# define S_MSC(c) (c == 'p' || c == 'n')
# define SPEC(c) (S_INT(c) || S_816(c) || S_REA(c) || S_CHA(c) || S_MSC(c))
# define FLAG(c) (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
# define MOD(c) (c == 'h' || c == 'l' || c == 'j' || c == 'z')
# define MAX(a, b) (a > b ? a : b)
# define MIN(a, b) (a < b ? a : b)
# define F_PREC 1
# define F_MINUS 2
# define F_PLUS 4
# define F_SPACE 8
# define F_HASH 16
# define F_ZERO 32

enum			e_modifiers
{
	NO, HH, H, L, LL, Z, J
};

typedef struct	s_frmt
{
	enum e_modifiers	mod;
/*	int					minus;
	int					plus;
	int					space;
	int					hash;
	int					zero;
	int					flag_prec;*/
	int					flags;
	int					precision;
	int					width;
	int					spec;
}				t_frmt;

int				ft_printf(const char *format, ...);
int				parse_format(const char **format, va_list argp);
int				print_formatted(va_list argp, t_frmt *params);
int				print_d(intmax_t n, t_frmt *params);
int				print_u(uintmax_t n, t_frmt *params);
int				print_o(uintmax_t n, t_frmt *params);
int				print_x(uintmax_t n, t_frmt *params);
int				print_f(double n, t_frmt *params);
int				print_c(const wchar_t c, t_frmt *params);
int				print_s(const char *s, t_frmt *params);
int				num_len(intmax_t n);
int				num_len_base(uintmax_t n, int base);
void			ntoa(char *s, intmax_t n);

#endif
