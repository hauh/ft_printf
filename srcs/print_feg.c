/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_feg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 18:18:09 by smorty            #+#    #+#             */
/*   Updated: 2019/05/12 22:26:11 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_exponent(long double *n)
{
	int exponent;

	if (!*n)
		return (0);
	exponent = 0;
	while (*n < 1 && *n > -1)
	{
		*n *= 10;
		exponent--;
	}
	while (*n > 10 || *n < -10)
	{
		*n /= 10;
		exponent++;
	}
	return (exponent);
}

long double	round_f(long double n, int precision)
{
	long double t;

	t = 0.5;
	while (precision)
	{
		t /= 10;
		precision--;
	}
	if (n > 0)
		n += t;
	else if (n < 0)
		n -= t;
	return (n);
}

void		prefix_fe(char *s, long double n, int flags)
{
	if (n < 0)
		*s = '-';
	else if (flags & F_PLUS)
		*s = '+';
	else if (flags & F_SPACE)
		*s = ' ';
}

void		fracttoa(char *s, double n, int precision)
{
	intmax_t t;

	if (precision)
	{
		*s = '.';
		s++;
		precision--;
		if (n < 0)
			n *= -1;
		t = n;
		n -= t;
		while (precision)
		{
			t = n * 10;
			*s = t + '0';
			n = n * 10 - t;
			s++;
			precision--;
		}
	}
}

int			print_feg(long double n, t_frmt *prm)
{
	long double e;

	if (!(prm->flags & F_PREC))
		prm->precision = 6;
	else if (prm->precision != 1)
		prm->precision--;
	if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		prm->flags ^= F_ZERO;
	if (prm->spec == 'g' || prm->spec == 'G')
	{
		e = n;
		e = get_exponent(&e);
		if ((int)e < prm->precision && (int)e >= -4)
			prm->precision -= (int)e + 1;
		else
		{
			prm->spec -= 2;
			prm->precision--;
		}
	}
	if (prm->spec == 'e' || prm->spec == 'E')
		return (print_e(n, prm));
	prm->len = num_len(n) + !(int)n;
	return (print_f(n, prm));
}
