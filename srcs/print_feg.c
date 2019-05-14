/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_feg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 18:18:09 by smorty            #+#    #+#             */
/*   Updated: 2019/05/14 21:31:16 by smorty           ###   ########.fr       */
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
	while (*n >= 10 || *n <= -10)
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

void				trim_zeros(char *s, int *precision)
{
	if (*precision)
	{
		while (*s == '0')
		{
			*s = ' ';
			s--;
			(*precision)--;
		}
		if (*s == '.')
		{
			*s = ' ';
			(*precision)--;
		}
	}
}

int					prefix_fe(char *s, long double n, int flags)
{
	if (n < 0)
		*s = '-';
	else if (flags & F_PLUS)
		*s = '+';
	else if (flags & F_SPACE)
		*s = ' ';
	else
		return (0);
	return (1);	
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
	char		spec;

	spec = prm->spec;
	if (!(prm->flags & F_PREC))
		prm->precision = 6;
	else if (prm->precision > 1)
		prm->precision--;
	if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		prm->flags ^= F_ZERO;
	e = n;
	i = get_exponent(&e);
	if (spec == 'g' || spec == 'G')
	{
		if (i < prm->precision && i >= -4)
			prm->precision -= i;
		else
			spec--;
		if (prm->precision > 0)
			prm->precision--;
		spec--;
	}
	prm->len = i;
	if (prm->len < 0)
		prm->len = ~prm->len + 1;
	if (spec == 'e' || spec == 'E')
		return (print_e(n, prm));
	return (print_f(n, prm));
}
