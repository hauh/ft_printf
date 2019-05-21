/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:40:04 by smorty            #+#    #+#             */
/*   Updated: 2019/05/21 18:04:45 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	suffix_e(char *s, int exponent, char spec)
{
	int len;

	len = 4;
	*s++ = spec - (spec == 'g' || spec == 'G' ? 2 : 0);
	*s++ = (exponent < 0 ? '-' : '+');
	if (exponent < 0)
		exponent = ~exponent + 1;
	if (exponent >= 1000)
	{
		*s++ = exponent / 1000 + '0';
		exponent %= 10;
		++len;
	}
	if (exponent >= 100)
	{
		*s++ = exponent / 100 + '0';
		exponent %= 10;
		++len;
	}
	*s++ = exponent / 10 + '0';
	*s = exponent % 10 + '0';
	return (len);
}

static void	etoa(char *s, long double n, t_frmt *prm)
{
	int precision;
	int exponent;

	precision = prm->precision;
	if ((int)n != (int)round_f(n, prm->precision))
		n = round_f(n, prm->precision);
	exponent = get_exponent(&n);
	s += prefix_fe(s, n, prm->flags);
	*s++ = (n < 0 ? -(int)n : (int)n) + '0';
	if (precision || prm->flags & F_HASH)
		*s++ = '.';
	fracttoa(s, n, precision);
	if ((prm->spec == 'g' || prm->spec == 'G') && !(prm->flags & F_HASH))
		trim_zeros(s + precision - 1, &precision);
	s += precision;
	*(s + suffix_e(s, exponent, prm->spec)) = 0;
}

void		process_e(long double n, t_frmt *prm)
{
	char	*out;

	prm->len = prm->len + prm->precision;
	if (n < 0 || prm->flags & (F_PLUS | F_SPACE))
		++prm->len;
	if (!(out = (char *)malloc(sizeof(char) * (prm->len + 1))))
	{
		g_error = -1;
		return ;
	}
	etoa(out, n, prm);
	prm->len = ft_strlen(out);
	*(out + prm->len) = 0;
	to_print(out, make_width(prm), prm);
}
