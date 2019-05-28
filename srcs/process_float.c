/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:37:10 by smorty            #+#    #+#             */
/*   Updated: 2019/05/28 17:35:38 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nan_or_inf(t_ld *nb, t_frmt *prm)
{
	if (nb->exponent == -0x4000)
	{
		if (prm->flags & F_PREC)
			(prm->flags ^= F_PREC);
		if (prm->flags & F_ZERO)
			(prm->flags ^= F_ZERO);
		if (!(nb->mantissa << 1))
		{
			if (nb->sign)
				process_s((prm->spec > 96 ? "-inf" : "-INF"), prm);
			else if (prm->flags & F_PLUS)
				process_s((prm->spec > 96 ? "+inf" : "+INF"), prm);
			else if (prm->flags & F_SPACE)
				process_s((prm->spec > 96 ? " inf" : " INF"), prm);
			else
				process_s((prm->spec > 96 ? "inf" : "INF"), prm);
		}
		else
			process_s((prm->spec > 96 ? "nan" : "NAN"), prm);
		return (1);
	}
	return (0);
}

void		suffix_float(char *out, int e, int spec)
{
	int r;

	*out++ = spec + (spec == 'a' || spec == 'A') * 15;
	*out++ = (e < 0 ? '-' : '+');
	if (!e)
	{
		*out++ = '0';
		if (spec != 'a' && spec != 'A')
			*out++ = '0';
	}
	else
	{
		if (e < 0)
			e = ~e + 1;
		r = 1;
		if (e < 10 && spec != 'a' && spec != 'A')
			*out++ = '0';
		while (e)
		{
			r = r * 10 + e % 10;
			e /= 10;
		}
		while (r != 1)
		{
			*out++ = r % 10 + '0';
			r /= 10;
		}
	}
	*out = 0;
}

void		process_float(va_list *argp, t_frmt *prm)
{
	t_bits		nb_union;
	t_ld		nb;

	prm->precision -= (prm->flags & F_PREC ? 1 : -7);
	if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		prm->flags ^= F_ZERO;
	if (prm->flags & F_LONGD)
		nb_union.l = va_arg(*argp, long double);
	else
		nb_union.l = va_arg(*argp, double);
	nb.exponent = nb_union.lsh[4] - 16383;
	nb.mantissa = *(uint64_t *)&nb_union.l;
	nb.sign = nb_union.lsh[4] >> 15;
	if (nan_or_inf(&nb, prm))
		return ;
	if ((prm->spec >= 'f' && prm->spec <= 'g') || (prm->spec >= 'F' && prm->spec <= 'G'))
		process_feg(&nb, prm);
	else if (prm->spec == 'a' || prm->spec == 'A')
		process_a(nb_union.l, nb.sign, prm);
}
