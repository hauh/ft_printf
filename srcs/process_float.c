/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:37:10 by smorty            #+#    #+#             */
/*   Updated: 2019/06/01 15:18:42 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nan_or_inf(t_ld *nb, t_frmt *prm)
{
	if (prm->flags & F_PREC)
		(prm->flags ^= F_PREC);
	if (prm->flags & F_ZERO)
		(prm->flags ^= F_ZERO);
	if (!(nb->mantissa << 1))
	{
		if (nb->sign)
			return (process_s((prm->spec > 96 ? "-inf" : "-INF"), prm));
		else if (prm->flags & F_PLUS)
			return (process_s((prm->spec > 96 ? "+inf" : "+INF"), prm));
		else if (prm->flags & F_SPACE)
			return (process_s((prm->spec > 96 ? " inf" : " INF"), prm));
		return (process_s((prm->spec > 96 ? "inf" : "INF"), prm));
	}
	return (process_s((prm->spec > 96 ? "nan" : "NAN"), prm));
}

void		suffix_float(char *out, int e, int spec)
{
	int r;

	*out++ = spec + (spec == 'a' || spec == 'A') * 15;
	*out++ = (e < 0 ? '-' : '+');
	if (e < 0)
		e = ~e + 1;
	if (e < 10 && spec != 'a' && spec != 'A')
		*out++ = '0';
	if (!e)
		*out++ = '0';
	else
	{
		r = 1;
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

int			process_float(va_list *argp, t_frmt *prm)
{
	t_bits		nb_union;
	t_ld		nb;

	if (!(prm->flags & F_PREC))
		prm->precision = 6;
	if (prm->flags & F_LONGD)
		nb_union.l = va_arg(*argp, long double);
	else
		nb_union.l = va_arg(*argp, double);
	nb.exponent = nb_union.lsh[4] - 16383;
	nb.mantissa = *(uint64_t *)&nb_union.l;
	nb.sign = nb_union.lsh[4] >> 15;
	if (nb.exponent == -0x4000)
		return (nan_or_inf(&nb, prm));
	if ((prm->spec >= 'f' && prm->spec <= 'g') || (prm->spec >= 'F' && prm->spec <= 'G'))
		return (process_feg(&nb, prm));
	else if (prm->spec == 'a' || prm->spec == 'A')
		return (process_a(nb_union.l, nb.sign, prm));
	return (0);
}
