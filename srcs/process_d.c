/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:27:53 by smorty            #+#    #+#             */
/*   Updated: 2019/05/27 17:58:37 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	dtoa(char **s, intmax_t n, int *precision)
{
	if (n < 0)
	{
		**s = n % 10 * -1 + '0';
		n = ~(n / 10) + 1;
		--(*s);
		--(*precision);
	}
	while (n)
	{
		**s = n % 10 + '0';
		n /= 10;
		--(*s);
		--(*precision);
	}
}

static int	prefix_d(char *out, int sign, int flags)
{
	if (sign)
		*out = '-';
	else if (flags & F_PLUS)
		*out = '+';
	else if (flags & F_SPACE)
		*out = ' ';
	else
		return (0);
	return (1);
}

static void	process_d_mod(intmax_t n, t_frmt *prm)
{
	char	*out;
	char	*out0;
	int		size;
	int		precision;

	precision = prm->precision - (prm->flags & F_PREC);
	size = MAX(precision, 20) + 1;
	out = (char *)malloc(sizeof(char) * (size + 1));
	ft_memset(out, '0', size);
	out0 = out;
	out += size;
	*out-- = 0;
	if (n)
		dtoa(&out, n, &precision);
	while (precision-- > 0)
		--out;
	if (!(prefix_d(out, (n < 0), prm->flags)))
		++out;
	prm->len = ft_strlen(out);
	to_print(out, make_width(prm), prm);
	free(out0);
}

void		process_d(va_list *argp, t_frmt *prm)
{
	if (prm->flags & F_ZERO)
	{
	 	if (prm->flags & (F_MINUS | F_PREC))
			prm->flags ^= F_ZERO;
		else if (prm->width > prm->precision)
		{
			prm->flags |= F_PREC;
			prm->precision = prm->width;
		}
	}
	if (prm->mod == HH)
		process_d_mod((char)va_arg(*argp, int), prm);
	else if (prm->mod == H)
		process_d_mod((short)va_arg(*argp, int), prm);
	else if (prm->mod == NO)
		process_d_mod(va_arg(*argp, int), prm);
	else if (prm->mod == L)
		process_d_mod(va_arg(*argp, long), prm);
	else if (prm->mod == LL)
		process_d_mod(va_arg(*argp, long long), prm);
	else if (prm->mod == Z)
		process_d_mod(va_arg(*argp, ssize_t), prm);
	else if (prm->mod == J)
		process_d_mod(va_arg(*argp, intmax_t), prm);
}
