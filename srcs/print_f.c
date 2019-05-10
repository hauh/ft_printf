/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:53:23 by smorty            #+#    #+#             */
/*   Updated: 2019/05/10 22:41:47 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void fracttoa(char *s, long double n, int precision)
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

static void	ftoa_flag(char *s, long double n, t_frmt *params, int flags, int size)
{
	int precision;
	int prefix;
	int len;

	precision = (*params).precision;
	n = round_f(n, precision);
	if (precision || flags & F_HASH)
		precision++;
	prefix = (n < 0 || flags & (F_PLUS | F_SPACE));
	len = ((int)n ? (*params).len : 1);
	if (flags & F_MINUS)
	{
		prefix_f(s, n, flags);
		if ((int)n)
			ntoa(s + len + prefix, n);
		else
			*(s + len + prefix - 1) = '0';
		fracttoa(s + len + prefix, n, precision);
	}
	else
	{
		s += size;
		if (!(flags & F_ZERO))
			prefix_f(s - len - precision - prefix, n, flags);
		if ((int)n)
			ntoa(s - precision, n);
		else
			*(s - precision - 1) = '0';
		fracttoa(s - precision, n, precision);
	}
}

int			print_f(long double n, t_frmt *params)
{
	char	*out;
	int		prefix;
	int		size;
	int		flags;
	int		printed;
	int		precision;

	flags = (*params).flags;
	precision = ((*params).precision ? (*params).precision + 1 : 0);
	prefix = (n < 0 || flags & (F_PLUS | F_SPACE));
	size = (*params).len + precision + prefix;
	if ((*params).spec == 'e' || (*params).spec == 'E')
		size += 4;
	size = MAX(size, (*params).width);
	if (!(out = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(out, (flags & F_ZERO ? '0' : ' '), size);
	*(out + size) = 0;
	ftoa_flag(out, n, params, flags, size);
	if (flags & F_ZERO)
		prefix_f(out, n, flags);
	printed = write((*params).fd, out, size);
	free(out);
	return (printed);
}