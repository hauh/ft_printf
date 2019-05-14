/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:53:23 by smorty            #+#    #+#             */
/*   Updated: 2019/05/14 19:34:19 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ftoa(char *s, long double n)
{
	long double d;
	int size;
	int len;

	if (!(int)n)
	{
		*s = '0';
		return (1);
	}
	if (n < 0)
		n *= -1;
	size = 1;
	d = n;
	while (d >= 10)
	{
		d /= 10;
		size++;
	}
	len = size;
	d = 1;
	while (size)
	{
		d *= 10;
		size--;
	}
	size = len;
	while (size)
	{
		d /= 10;
		*s = (int)(n / d);
		n -= *s * d;
		*s += '0';
		size--;
		s++;
	}
	return (len);
}

static void	floattoa(char *s, long double n, t_frmt *prm)
{
	long double z;
	int precision;
	int exponent;

	precision = prm->precision;
	if ((int)n != (int)round_f(n, prm->precision))
		n = round_f(n, prm->precision);
	s += prefix_fe(s, n, prm->flags);
	s += ftoa(s, n);
	if (precision || prm->flags & F_HASH)
		*s++ = '.';
	fracttoa(s, n, precision);
	if ((prm->spec == 'g' || prm->spec == 'G') && !(prm->flags & F_HASH))
		trim_zeros(s + precision - 1, &precision);
	*(s + precision) = 0;
}

int print_f(long double n, t_frmt *prm)
{
	char *out;
	char *width;
	int prefix;

	prefix = (n < 0 || prm->flags & (F_PLUS | F_SPACE));
	prm->len = prm->len + prm->precision + prefix;
	if (!(out = (char *)malloc(sizeof(char) * prm->len)))
		return (-1);
	floattoa(out, n, prm);
	prm->len = ft_strlen(out);
	if (prm->width > prm->len)
	{
		prm->width -= prm->len;
		if (!(width = (char *)malloc(sizeof(char) * prm->width)))
			return (-1);
		ft_memset(width, (prm->flags & F_ZERO ? '0' : ' '), prm->width);
	}
	else
		width = NULL;
	return (print(out, width, prm));
}