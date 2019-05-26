/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:29:52 by smorty            #+#    #+#             */
/*   Updated: 2019/05/26 22:47:27 by smorty           ###   ########.fr       */
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
	while (ABS(*n) >= max)
	{
		*n /= 2;
		++p;
	}
	if (*n)
		while (ABS(*n) < min)
		{
			*n *= 2;
			--p;
		}
	return (p);
}

static int round_a(char *s, int spec)
{
	int dif;

	if (*s >= 8)
	{
		--s;
		dif = 1;
		while (dif && *s != '.')
		{
			++(*s);
			*s > 15 ? (*s = 0) : (dif = 0);
			--s;
		}
		if (dif)
		{
			(*(s - 1))++;
			if (*(s - 1) == spec + 6)
			{
				*(s - 1) = '1';
				return (4);
			}
		}
	}
	return (0);	
}

static void	fracttohex(char **out, long double n, int p, t_frmt *prm)
{
	if (n < 0)
	{
		*(*out)++ = '-';
		n *= -1;
	}
	else if (prm->flags & F_PLUS)
		*(*out)++ = '+';
	else if (prm->flags & F_SPACE)
		*(*out)++ = ' ';
	*(*out)++ = '0';
	*(*out)++ = prm->spec + 23;
	*(*out)++ = (int)n + ((int)n > 9 ? prm->spec - 10 : '0');
	*(*out)++ = '.';
	n -= (int)n;
	while (n)
	{
		n *= 16;
		**out = (int)n;
		n -= (int)n;
		++(*out);
	}
}

void		process_a_mod(long double n, t_frmt *prm)
{
	int p;
	char *out;
	char *out0;

	p = get_exponent(&n, prm->flags & F_LONGD);
	out = (char *)malloc(sizeof(char) * (30 + prm->precision));
	ft_bzero(out, 30 + prm->precision);
	out0 = out;
	fracttohex(&out, n, p, prm);
	if (prm->flags & F_PREC)
	{
		out = out0 + 4 + (n < 0 || prm->flags & (F_PLUS | F_SPACE));
		out += prm->precision;
		p += (round_a(out + !(prm->precision), prm->spec));
		if (!prm->precision)
			--out;
	}
	*out++ = prm->spec + 15;
	*out++ = (p < 0 ? '-' : '+');
	*out++ = (p < 0 ? -p : p) + '0';
	*out = 0;
	if (prm->precision)
	{
		while (*out != 'p')
			--out;
		--out;
		while (*out != '.')
		{
			*out += (*out > 9 ? prm->spec - 10 : '0');
			--out;
		}
	}
	prm->len = ft_strlen(out0);
	to_print(out0, make_width(prm), prm);
	free(out0);
}

void		process_a(va_list *argp, t_frmt *prm)
{
	if (prm->flags & F_PREC)
		--prm->precision;
	else
		prm->precision = 6;
	if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		prm->flags ^= F_ZERO;
	if (prm->flags & F_LONGD)
		process_a_mod(va_arg(*argp, long double), prm);
	else
		process_a_mod(va_arg(*argp, double), prm);
}
