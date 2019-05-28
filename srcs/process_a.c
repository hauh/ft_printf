/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:29:52 by smorty            #+#    #+#             */
/*   Updated: 2019/05/28 22:14:42 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_exponent(long double *n, int flag_ld)
{
	int p;
	int m;

	p = 0;
	if (*n < 0)
		*n *= -1;
	m = (flag_ld ? 16 : 2);
	while (*n >= m)
	{
		*n /= 2;
		++p;
	}
	m = (flag_ld ? 8 : 1);
	if (*n)
		while (*n < m)
		{
			*n *= 2;
			--p;
		}
	return (p);
}

static int	prefix_a(char *out, int sign, t_frmt *prm)
{
	char *out0;

	out0 = out;
	if (sign)
		*out++ = '-';
	else if (prm->flags & F_PLUS)
		*out++ = '+';
	else if (prm->flags & F_SPACE)
		*out++ = ' ';
	*out++ = '0';
	*out++ = prm->spec + 23;
	return (out - out0);
}

static int	round_a(char *s, int spec)
{
	int dif;

	dif = 1;
	while (*--s != '.' && dif)
	{
		*s += (*s == '9' ? spec - '9' : 1);
		if (*s == spec + 6)
			*s = '0';
		else
			dif = 0;
	}
	if (dif)
	{
		--s;
		*s += (*s == '9' ? spec - '9' : 1);
		if (*s == spec + 6)
		{
			*s = '1';
			return (4);
		}
	}
	return (0);
}

static void	floattohex(char *out, long double n, t_frmt *prm)
{
	int p;

	p = get_exponent(&n, prm->flags & F_LONGD);
	*out++ = (int)n + ((int)n > 9 ? prm->spec - 10 : '0');
	n -= (int)n;
	*out++ = '.';
	while (n && (prm->flags & F_PREC ? prm->precision : 1))
	{
		n *= 16;
		*out++ = (int)n + ((int)n > 9 ? prm->spec - 10 : '0');
		n -= (int)n;
		--prm->precision;
	}
	if (prm->flags & F_PREC)
	{
		n *= 16;
		if (prm->precision)
			out += prm->precision;
		else if ((int)n > 8 || ((int)n == 8 && ((int)(n * 16) % 2)))
			p += round_a(out, prm->spec);
	}
	if (*(out - 1) == '.' && !(prm->flags & F_HASH))
		--out;
	suffix_float(out, p, prm->spec);
}

void		process_a(long double n, int sign, t_frmt *prm)
{
	char *out;
	char *out0;
	char *width;

	out = (char *)malloc(sizeof(char) * (30 + prm->precision));
	ft_memset(out, '0', 30 + prm->precision);
	out0 = out;
	out += prefix_a(out, sign, prm);
	floattohex(out, n, prm);
	if (prm->flags & F_ZERO && prm->width > 6)
	{
		prm->len = ft_strlen(out);
		if (prm->width - prm->len < out - out0)
			prm->width = 0;
	}
	else
		prm->len = ft_strlen(out0);
	width = make_width(prm);
	if (width && prm->flags & F_ZERO)
		prefix_a(width, sign, prm);
	to_print((width && prm->flags & F_ZERO ? out : out0), width, prm);
	free(out0);
}