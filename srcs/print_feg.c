/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_feg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 18:18:09 by smorty            #+#    #+#             */
/*   Updated: 2019/05/13 22:53:00 by smorty           ###   ########.fr       */
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
		exponent--;
	}
	while (*n > 10 || *n < -10)
	{
		*n /= 10;
		exponent++;
	}
	return (exponent);
}

long double			round_f(long double n, int precision)
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

void				prefix_fe(char *s, long double n, int flags)
{
	if (n < 0)
		*s = '-';
	else if (flags & F_PLUS)
		*s = '+';
	else if (flags & F_SPACE)
		*s = ' ';
}

static void			round_fract(char *s)
{
	int diff;

	diff = 1;
	while (*s != '.' && diff)
	{
		s--;
		(*s)++;
		if (*s > '9')
			*s = '0';
		else
			diff = 0;
	}
}

void				fracttoa(char *s, double n, int precision)
{
	if (precision)
	{
		*s = '.';
		s++;
		precision--;
		if (n < 0)
			n *= -1;
		n -= (intmax_t)n;
		while (precision)
		{
			n = n * 10;
			*s = (int)n + '0';
			n -= (int)n;
			s++;
			precision--;
		}
		n = n * 10;
		if ((int)n >= 5)
			round_fract(s);
	}
}

int					print_feg(long double n, t_frmt *prm)
{
	long double	e;
	int			i;

	if (!(prm->flags & F_PREC))
		prm->precision = 6;
	if (prm->precision > 1)
		prm->precision--;
	if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		prm->flags ^= F_ZERO;
	e = n;
	i = get_exponent(&e);
	if (prm->spec == 'g' || prm->spec == 'G')
	{
		if (i < prm->precision && i >= -4)
			prm->precision -= i;
		else
			prm->spec -= 2;
		if (prm->precision > 0)
			prm->precision--;
	}
	prm->len = (i < 0 ? -i : i) + 1;
	if (prm->precision || prm->flags & F_HASH)
		prm->precision++;
	if (prm->spec == 'e' || prm->spec == 'E')
		return (print_e(n, prm));
	return (print_f(n, prm));
}
