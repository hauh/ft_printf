/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_eg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:21:08 by smorty            #+#    #+#             */
/*   Updated: 2019/05/10 23:11:48 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_exponent(long double *n)
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

static void	suffix_e(char *s, int exponent, char spec)
{
	*s = spec;
	if (exponent < 0)
	{
		*(s + 1) = '-';
		exponent *= -1;
	}
	else
		*(s + 1) = '+';
	*(s + 2) = exponent / 10 + '0';
	*(s + 3) = exponent % 10 + '0';
}

static void	etoa(char *s, long double n, int size, t_frmt *params)
{
	int precision;
	int exponent;
	int prefix;
	int flags;

	flags = (*params).flags;
	precision = (*params).precision;
	exponent = get_exponent(&n);
	n = round_f(n, precision);
	if (precision || flags & F_HASH)
		precision++;
	prefix = (n < 0 || flags & (F_PLUS | F_SPACE));
	if (flags & F_MINUS)
	{
		*(s + prefix) = (n < 0 ? -(int)n : (int)n) + '0';
		fracttoa(s + prefix + 1, n, precision);
		suffix_e(s + prefix + 1 + precision, exponent, (*params).spec);
		return ;
	}
	s += size;
	if (!(flags & F_ZERO))
		prefix_f(s - 5 - prefix - precision, n, flags);
	*(s - 5 - precision) = (n < 0 ? -(int)n : (int)n) + '0';
	fracttoa(s - 4 - precision, n, precision);
	suffix_e(s - 4, exponent, (*params).spec);
}

int			print_e(long double n, t_frmt *params)
{
	char	*out;
	int		printed;
	int		prefix;
	int		flags;
	int		size;

	flags = (*params).flags;
	prefix = (n < 0 || flags & (F_PLUS | F_SPACE));
	size = ((*params).precision ? (*params).precision + 1 : 0);
	if (!size && flags & F_HASH)
		size++;
	size = MAX(size + 5 + prefix, (*params).width);
	out = (char *)malloc(sizeof(char) * size);
	ft_memset(out, (flags & F_ZERO ? '0' : ' '), size);
	etoa(out, n, size, params);
	if (flags & (F_MINUS | F_ZERO))
		prefix_f(out, n, flags);
	printed = write(1, out, size);
	free(out);
	return (printed);
}

int			print_feg(long double n, t_frmt *params)
{
	long double	e;

	if (!((*params).flags & F_PREC))
		(*params).precision = 6;
	else if ((*params).precision != 1)
		(*params).precision--;
	if (((*params).flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		(*params).flags ^= F_ZERO;
	if ((*params).spec == 'g' || (*params).spec == 'G')
	{
		e = n;
		e = get_exponent(&e);
		if ((int)e < (*params).precision && (int)e >= -4)
			(*params).precision -= (int)e;
		else
			(*params).spec--;
		(*params).precision--;
		(*params).spec--;
	}
	if ((*params).spec == 'e' || (*params).spec == 'E')
		return (print_e(n, params));
	(*params).len = num_len(n);
	return (print_f(n, params));
}
