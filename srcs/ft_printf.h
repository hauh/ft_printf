/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:08:11 by smorty            #+#    #+#             */
/*   Updated: 2019/05/15 20:55:57 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <wchar.h>

# define S_INT(c) (c == 'i' || c == 'd' || c == 'D' || c == 'u' || c == 'U')
# define S_BAS(c) (c == 'o' || c == 'O' || c == 'x' || c == 'X' || c == 'b' || c == 'B')
# define S_REA(c) (c == 'f' || c == 'F' || c == 'e' || c == 'E' || c == 'g' || c == 'G')
# define S_CHA(c) (c == 'c'	|| c == 'C' || c == 's' || c == 'S')
# define S_MSC(c) (c == 'p' || c == 'n')
# define SPEC(c) (S_INT(c) || S_BAS(c) || S_REA(c) || S_CHA(c) || S_MSC(c))
# define FLAG(c) (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0')
# define MOD(c) (c == 'h' || c == 'l' || c == 'j' || c == 'z' || c == 'L')
# define MAX(a, b) (a > b ? a : b)
# define MIN(a, b) (a < b ? a : b)
# define F_PREC 1
# define F_MINUS 2
# define F_PLUS 4
# define F_SPACE 8
# define F_HASH 16
# define F_ZERO 32

#define BUFF_SIZE 256

extern char	*g_buf;
extern int	g_len;
extern int	g_printed;
extern int	g_error;

enum			e_modifiers
{
	NO, HH, H, L, LL, Z, J, LD
};

typedef struct	s_frmt
{
	enum e_modifiers	mod;
	int					flags;
	int					len;
	int					precision;
	int					width;
	int					spec;
	int					fd;
}				t_frmt;

int				ft_printf(const char *format, ...);
void			parse_format(const char **format, va_list argp);
void			print_formatted(va_list argp, t_frmt *prm);
void			print_d(intmax_t n, t_frmt *prm);
void			print_u(uintmax_t n, t_frmt *prm);
void			print_o(uintmax_t n, t_frmt *prm);
void			print_x(uintmax_t n, t_frmt *prm);
void			print_b(uintmax_t n, t_frmt *prm);
void			print_f(long double n, t_frmt *prm);
void			print_e(long double n, t_frmt *prm);
void			print_feg(long double n, t_frmt *prm);
void			print_c(const wchar_t c, t_frmt *prm);
void			print_s(char *s, t_frmt *prm);
void			print_ws(wchar_t *s, t_frmt *prm);
int				num_len(intmax_t n);
void			ntoa(char *s, intmax_t n);
void			fracttoa(char *s, double n, int precision);
int				prefix_fe(char *s, long double n, int flags);
long double		round_f(long double n, int precision);
int				get_exponent(long double *n);
void			trim_zeros(char *s, int *precision);
void			print(char *out, char *width, t_frmt *prm);
char			*get_width(t_frmt *prm);
void			print_buf(void);
void			move_to_buf(char *s);
void			error(void);

#endif
