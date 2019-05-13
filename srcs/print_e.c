/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:21:08 by smorty            #+#    #+#             */
/*   Updated: 2019/05/13 23:00:50 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	suffix_e(char *s, int exponent, char spec)
{
	*s = spec;
	if (exponent < 0)
	{
		*(s + 1) = '-';
		exponent = ~exponent + 1;
	}
	else
		*(s + 1) = '+';
	if (exponent > 99)
	{
		*(s + 2) = exponent / 100 + '0';
		exponent %= 100;
		s++;
	}
	*(s + 2) = exponent / 10 + '0';
	*(s + 3) = exponent % 10 + '0';
}

static void	etoa(char *s, long double n, int size, t_frmt *prm)
{
	int precision;
	int exponent;
	int prefix;
	int flags;

	flags = prm->flags;
	precision = prm->precision;
	exponent = get_exponent(&n);
	n = round_f(n, prm->precision);
	prefix = (n < 0 || flags & (F_PLUS | F_SPACE));
	if (flags & F_MINUS)
	{
		*(s + prefix) = (n < 0 ? -(int)n : (int)n) + '0';
		fracttoa(s + prefix + 1, n, precision);
		suffix_e(s + prefix + 1 + precision, exponent, prm->spec);
	}
	else
	{
		s += size;
		if (!(flags & F_ZERO))
			prefix_fe(s - 5 - prefix - precision, n, flags);
		*(s - 5 - precision) = (n < 0 ? -(int)n : (int)n) + '0';
		fracttoa(s - 4 - (prm->len - 1 > 99) - precision, n, precision);
		suffix_e(s - 4 - (prm->len - 1 > 99), exponent, prm->spec);
	}
}

int			print_e(long double n, t_frmt *prm)
{
	char	*out;
	int		printed;
	int		prefix;
	int		flags;
	int		size;

	flags = prm->flags;
	prefix = (n < 0 || flags & (F_PLUS | F_SPACE));
	size = MAX(prm->precision + 5 + (prm->len - 1 > 99) + prefix, prm->width);
	out = (char *)malloc(sizeof(char) * size);
	ft_memset(out, (flags & F_ZERO ? '0' : ' '), size);
	etoa(out, n, size, prm);
	if (flags & (F_MINUS | F_ZERO))
		prefix_fe(out, n, flags);
	printed = write(prm->fd, out, size);
	free(out);
	return (printed);
}
