/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:29:52 by smorty            #+#    #+#             */
/*   Updated: 2019/05/27 23:32:55 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_exponent(long double *n, int flag_ld)
{
	int p;
	int min;
	int max;

	p = 0;
	min = (flag_ld ? 8 : 1);
	max = (flag_ld ? 15 : 2);
	if (*n < 0)
		*n *= -1;
	while (*n >= max)
	{
		*n /= 2;
		++p;
	}
	if (*n)
		while (*n < min)
		{
			*n *= 2;
			--p;
		}
	return (p);
}

static int round_a(char *s, int spec)
{
	int dif;

	if (*s >= spec || *s == '9' || (*s == '8' && !(*(s - 1) % 2)))
	{
		--s;
		dif = 1;
		while (dif && *s != '.')
		{
			if (*s == '9')
				*s = spec;
			else
				++(*s);			
			(*s == spec + 6) ? (*s = '0') : (dif = 0);
			--s;
		}
		if (dif && (*(s + 1) != '8' || !(*(s - 1) % 2)))
		{
			--s;
			++(*s);
			if (*s == '9' + 1)
				*s = spec;
			else if (*s == spec + 6)
			{
				*s = '1';
				return (4);
			}
		}
	}
	return (0);	
}

static int prefix_a(char *out, int sign, t_frmt *prm)
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

static void suffix_a(char *out, int p, int spec)
{
	int tmp;

	*out++ = spec + 15;
	*out++ = (p < 0 ? '-' : '+');
	if (!p)
		*out++ = '0';
	else
	{
		if (p < 0)
			p = ~p + 1;
		tmp = 1;
		while (p)
		{
			tmp = tmp * 10 + p % 10;
			p /= 10;
		}
		while (tmp != 1)
		{
			*out++ = tmp % 10 + '0';
			tmp /= 10;
		}
	}
	*out = 0;
}

static void		floattohex(char *out, long double n, t_frmt *prm)
{
	int p;
	char *dot;

	p = get_exponent(&n, prm->flags & F_LONGD);
	*out++ = (int)n + ((int)n > 9 ? prm->spec - 10 : '0');
	n -= (int)n;
	if (n || prm->precision || prm->flags & F_HASH)
	{
		*out++ = '.';
		dot = out;
		while (n)
		{
			n *= 16;
			*out = (int)n + ((int)n > 9 ? prm->spec - 10 : '0');
			n -= (int)n;
			++out;
		}
		if (prm->flags & F_PREC)
		{
			p += round_a(dot + prm->precision, prm->spec);
			out = dot + prm->precision;
			if (!prm->precision && !(prm->flags & F_HASH))
				out--;
		}
	}
	suffix_a(out, p, prm->spec);
}

void		process_a(va_list *argp, t_frmt *prm)
{
	long double n;
	char *out;
	char *out0;
	char *width;

	if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		prm->flags ^= F_ZERO;
	--prm->precision;
	n = (prm->flags & F_LONGD ? va_arg(*argp, long double) : va_arg(*argp, double));
	out = (char *)malloc(sizeof(char) * (30 + prm->precision));
	ft_memset(out, '0', 30 + prm->precision);
	out0 = out;
	out += prefix_a(out, (n < 0), prm);
	floattohex(out, n, prm);
	if (prm->flags & F_ZERO && prm->width > 8)
	{
		prm->len = ft_strlen(out);
		if (prm->width - prm->len < out - out0)
			prm->width = 0;
	}
	else
		prm->len = ft_strlen(out0);
	width = make_width(prm);
	if (width && prm->flags & F_ZERO)
	{
		prefix_a(width, (n < 0), prm);
		to_print(out, width, prm);
	}
	else
		to_print(out0, width, prm);
	free(out0);
}
