/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:27:53 by smorty            #+#    #+#             */
/*   Updated: 2019/05/21 18:04:29 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_d(intmax_t n)
{
	intmax_t	d;
	int			size;

	size = 1;
	n /= (n < 0 ? -10 : 10);
	d = 1;
	while (d <= n)
	{
		d *= 10;
		size++;
	}
	return (size);
}

static void	dtoa(char *s, intmax_t n)
{
	if (n < 0)
	{
		s--;
		*s = n % 10 * -1 + '0';
		n = ~(n / 10) + 1;
	}
	while (n)
	{
		s--;
		*s = n % 10 + '0';
		n /= 10;
	}
}

static void	prefix_d(char *s, int sign, int flags)
{
	if (sign)
		*s = '-';
	else if (flags & F_PLUS)
		*s = '+';
	else if (flags & F_SPACE)
		*s = ' ';
}

static void	process_d_mod(intmax_t n, t_frmt *prm)
{
	char	*out;
	char	*width;
	int		flags;
	int		precision;

	if (prm->flags & F_ZERO && prm->flags & (F_MINUS | F_PREC))
		prm->flags ^= F_ZERO;
	flags = prm->flags;
	precision = prm->precision - (flags & F_PREC);
	prm->len = num_len_d(n);
	prm->len = MAX(prm->len, precision) + (n < 0 || flags & (F_PLUS | F_SPACE));
	if (!(out = (char *)malloc(sizeof(char) * (prm->len + 1))))
	{
		g_error = -1;
		return ;
	}
	ft_memset(out, '0', prm->len);
	if (!n && !precision)
		prm->len = 0;
	else
		dtoa(out + prm->len, n);
	*(out + prm->len) = 0;
	width = make_width(prm);
	prefix_d((width && (flags & F_ZERO) ? width : out), (n < 0), flags);
	to_print(out, width, prm);
}

void		process_d(va_list *argp, t_frmt *params)
{
	if ((*params).mod == HH)
		process_d_mod((char)va_arg(*argp, int), params);
	else if ((*params).mod == H)
		process_d_mod((short)va_arg(*argp, int), params);
	else if ((*params).mod == NO)
		process_d_mod(va_arg(*argp, int), params);
	else if ((*params).mod == L)
		process_d_mod(va_arg(*argp, long), params);
	else if ((*params).mod == LL)
		process_d_mod(va_arg(*argp, long long), params);
	else if ((*params).mod == Z)
		process_d_mod(va_arg(*argp, ssize_t), params);
	else if ((*params).mod == J)
		process_d_mod(va_arg(*argp, intmax_t), params);
}
