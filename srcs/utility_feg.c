/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_feg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:08:17 by smorty            #+#    #+#             */
/*   Updated: 2019/05/21 16:38:58 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	round_f(long double n, int precision)
{
	long double t;

	t = 0.5;
	while (precision)
	{
		t /= 10;
		--precision;
	}
	if (n > 0)
		n += t;
	else if (n < 0)
		n -= t;
	return (n);
}

void		trim_zeros(char *s, int *precision)
{
	if (*precision)
	{
		while (*s == '0')
		{
			*s = ' ';
			--s;
			--(*precision);
		}
		if (*s == '.')
		{
			*s = ' ';
			--(*precision);
		}
	}
}

int			prefix_fe(char *s, long double n, int flags)
{
	if (n < 0 || 1 / n < 0)
		*s = '-';
	else if (flags & F_PLUS)
		*s = '+';
	else if (flags & F_SPACE)
		*s = ' ';
	else
		return (0);
	return (1);
}

static void	round_fract(char *s)
{
	int diff;

	diff = 1;
	while (*s != '.' && diff)
	{
		--s;
		++(*s);
		if (*s > '9')
			*s = '0';
		else
			diff = 0;
	}
}

void		fracttoa(char *s, long double n, int precision)
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
			++s;
			--precision;
		}
		n = n * 10;
		if ((int)n >= 5)
			round_fract(s);
	}
}
