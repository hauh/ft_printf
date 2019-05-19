/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 20:24:09 by smorty            #+#    #+#             */
/*   Updated: 2019/05/19 19:57:40 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_b(uintmax_t n)
{
	uintmax_t	d;
	int			size;

	size = 1;
	n /= 2;
	d = 1;
	while (d <= n)
	{
		d *= 2;
		size++;
	}
	return (size);
}

static void	btoa(char *s, uintmax_t n)
{
	while (n)
	{
		s--;
		*s = n % 2 + '0';
		n /= 2;
	}
}

static void	prefix_b(char *s, int n_is_zero, t_frmt *prm)
{
	if (!n_is_zero && prm->flags & F_HASH)
	{
		*s = '0';
		*(s + 1) = prm->spec;
	}
}

static void	process_b_mod(uintmax_t n, t_frmt *prm)
{
	char	*out;
	char	*width;
	int		prec;

	if (prm->flags & F_ZERO && prm->flags & (F_MINUS | F_PREC))
		prm->flags ^= F_ZERO;
	prec = prm->precision - (prm->flags & F_PREC);
	prm->len = MAX(num_len_b(n), prec) + (n && (prm->flags & F_HASH) ? 2 : 0);
	if (!(out = (char *)malloc(sizeof(char) * (prm->len + 1))))
	{
		g_error = -1;
		return ;
	}
	ft_memset(out, '0', prm->len);
	if (!n && !prec)
		prm->len = 0;
	else
		btoa(out + prm->len, n);
	width = make_width(prm);
	prefix_b((width && (prm->flags & F_ZERO) ? width : out), !n, prm);
	to_print(out, width, prm);
}

void		process_b(va_list argp, t_frmt *params)
{
	if ((*params).mod == HH)
		process_b_mod((unsigned char)va_arg(argp, unsigned int), params);
	else if ((*params).mod == H)
		process_b_mod((unsigned short)va_arg(argp, unsigned int), params);
	else if ((*params).mod == NO)
		process_b_mod(va_arg(argp, unsigned int), params);
	else if ((*params).mod == L)
		process_b_mod(va_arg(argp, unsigned long), params);
	else if ((*params).mod == LL)
		process_b_mod(va_arg(argp, unsigned long long), params);
	else if ((*params).mod == Z)
		process_b_mod(va_arg(argp, size_t), params);
	else if ((*params).mod == J)
		process_b_mod(va_arg(argp, uintmax_t), params);
}
