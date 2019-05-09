/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:53:23 by smorty            #+#    #+#             */
/*   Updated: 2019/05/09 20:38:41 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void fracttoa(char *s, double n, int precision)
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

double round_f(double n, int precision)
{
	double t;

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

static void	prefix_f(char *s, double n, int flags)
{
	if (n < 0)
		*s = '-';
	else if (flags & F_PLUS)
		*s = '+';
	else if (flags & F_SPACE)
		*s = ' ';
}

static void	ftoa_flag(char *s, double n, t_frmt *params, int flags, int size)
{
	int precision;
	int prefix;
	int len;

	precision = (*params).precision - (flags & F_PREC);
	n = round_f(n, precision);
	if (precision)
		precision++;
	prefix = (n < 0 || flags & F_PLUS || flags & F_SPACE);
	len = (n ? num_len(n) : 1);
	if (flags & F_MINUS)
	{
		fracttoa(s + len + prefix, n, precision);
		if (n)
			ntoa(s + len + prefix, n);
		else
			*(s + len + prefix - 1) = '0';
		prefix_f(s, n, flags);
	}
	else
	{
		s += size;
		fracttoa(s - precision, n, precision);
		if (n)
			ntoa(s - precision, n);
		else
			*(s - precision - 1) = '0';
		if (!(flags & F_ZERO))
			prefix_f(s - len - precision - prefix, n, flags);
	}
}

int print_f(double n, t_frmt *params)
{
	char	*s;
	int		prefix;
	int		size;
	int		flags;
	int		printed;
	int		precision;

	flags = (*params).flags;
	if (flags & F_ZERO && flags & F_MINUS)
		flags ^= F_ZERO;
	precision = ((*params).precision ? (*params).precision - (flags & F_PREC) + 1 : 0);
	prefix = (n < 0 || flags & F_PLUS || flags & F_SPACE);
	size = num_len(n) + precision + prefix;
	size = MAX(size, (*params).width);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	*(s + size) = 0;
	ftoa_flag(s, n, params, flags, size);
	if (flags & F_ZERO)
		prefix_f(s, n, flags);
	printed = write(1, s, size);
	free(s);
	return (printed);
}