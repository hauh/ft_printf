/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_feg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 18:18:09 by smorty            #+#    #+#             */
/*   Updated: 2019/05/21 16:10:34 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					get_exponent(long double *n)
{
	int exponent;

	if (!*n)
		return (0);
	exponent = 0;
	while (*n < 1 && *n > -1)
	{
		*n *= 10;
		--exponent;
	}
	while (*n >= 10 || *n <= -10)
	{
		*n /= 10;
		++exponent;
	}
	return (exponent);
}

static int			nan_or_inf(long double n, t_frmt *prm)
{
	if (n != n)
	{
		if (prm->flags & F_PREC)
			(prm->flags ^= F_PREC);
		process_s((prm->spec > 100 ? "nan" : "NAN"), prm);
		return (1);
	}
	if (n && n * 2 == n)
	{
		if (prm->flags & F_PREC)
			(prm->flags ^= F_PREC);
		if (n < 0)
			process_s((prm->spec > 100 ? "-inf" : "-INF"), prm);
		else if (prm->flags & F_PLUS)
			process_s((prm->spec > 100 ? "+inf" : "+INF"), prm);
		else if (prm->flags & F_SPACE)
			process_s((prm->spec > 100 ? " inf" : " INF"), prm);
		else
			process_s((prm->spec > 100 ? "inf" : "INF"), prm);
		return (1);
	}
	return (0);
}

static void			process_feg_mod(long double n, t_frmt *prm)
{
	long double	e;
	int			i;
	int			spec;

	if (nan_or_inf(n, prm))
		return ;
	spec = prm->spec;
	e = n;
	i = get_exponent(&e);
	if (spec == 'g' || spec == 'G')
	{
		if (i < prm->precision && i >= -4)
			prm->precision -= i;
		else
			--spec;
		if (prm->precision > 0)
			--prm->precision;
		--spec;
	}
	prm->len = (i < 0 ? ~i + 1 : i);
	if (spec == 'e' || spec == 'E')
		process_e(n, prm);
	else
		process_f(n, prm);
}

void				process_feg(va_list *argp, t_frmt *prm)
{
	if (!(prm->flags & F_PREC))
		prm->precision = 6;
	else if (prm->precision > 1)
		--prm->precision;
	if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		prm->flags ^= F_ZERO;
	if (prm->flags & F_LONGD)
		process_feg_mod(va_arg(*argp, long double), prm);
	else
		process_feg_mod(va_arg(*argp, double), prm);
}
