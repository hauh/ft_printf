/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:08:11 by smorty            #+#    #+#             */
/*   Updated: 2019/05/24 21:00:31 by smorty           ###   ########.fr       */
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

# define F_PREC 1
# define F_MINUS 2
# define F_PLUS 4
# define F_SPACE 8
# define F_HASH 16
# define F_ZERO 32
# define F_LONGD 64

# define MAX(a, b) (a > b ? a : b)
# define MIN(a, b) (a < b ? a : b)
# define ABS(x) (x < 0 ? ~x + 1 : x)
# define CHECK_BUFF(x) (g_len + x > BUFF_SIZE ? print_buf() : 0)

# define COLOR_RED     "\x1b[31m"
# define COLOR_GREEN   "\x1b[32m"
# define COLOR_YELLOW  "\x1b[33m"
# define COLOR_BLUE    "\x1b[34m"
# define COLOR_MAGENTA "\x1b[35m"
# define COLOR_CYAN    "\x1b[36m"
# define COLOR_RESET   "\x1b[0m"

# define BUFF_SIZE 128

extern char	g_buf[BUFF_SIZE];
extern int	g_len;
extern int	g_printed;
extern int	g_error;
extern int	g_fd;

enum			e_modifiers
{
	NO, HH, H, L, LL, Z, J,
};

typedef struct	s_frmt
{
	enum e_modifiers	mod;
	int					flags;
	int					len;
	int					precision;
	int					width;
	int					spec;
}				t_frmt;

typedef union	u_bits
{
	long double			l;
	short				lsh[5];
}				t_bits;

typedef struct	s_ld
{
	uint64_t			mantissa: 64;
	int					exponent: 15;
	int					sign: 1;
}				t_ld;



int				ft_printf(const char *format, ...);
void			check_color_and_fd(const char **format);
void			parse_params(const char **format, va_list *argp, t_frmt prm);
void			process_format(va_list *argp, t_frmt *prm);
void			process_d(va_list *argp, t_frmt *prm);
void			process_u(va_list *argp, t_frmt *prm);
void			process_o(va_list *argp, t_frmt *prm);
void			process_x(va_list *argp, t_frmt *prm);
void			process_b(va_list *argp, t_frmt *prm);
void			process_c(const wchar_t c, t_frmt *prm);
void			process_s(const char *s, t_frmt *prm);
void			process_cs(va_list *argp, t_frmt *prm);
void			process_feg(va_list *argp, t_frmt *prm);
int				unicode(wchar_t c);
long double		round_f(long double n, int precision);
void			print_buf(void);
void			char_to_buf(char c, int n);
void			string_to_buf(char *s);
char			*make_width(t_frmt *prm);
void			to_print(char *out, char *width, t_frmt *prm);

#endif
