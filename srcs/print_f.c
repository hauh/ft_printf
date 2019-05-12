/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:53:23 by smorty            #+#    #+#             */
/*   Updated: 2019/05/12 23:06:14 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	trim_zeros(char *s, int width, t_frmt *prm)
{
	int printed;

	if (prm->flags & F_MINUS)
	{
		while (*s == ' ' || *s == '0')
		{
			if (*s == '0')
				*s = (width ? ' ' : 0);
			s--;
		}
		if (*s == '.')
			*s = (width ? ' ' : 0);
		return (0);
	}
	printed = 0;
	while (*s == '0')
	{
		*s = 0;
		s--;
		printed += (width ? write(prm->fd, " ", 1) : 0);
	}
	if (*s == '.')
	{
		*s = 0;
		printed += (width ? write(prm->fd, " ", 1) : 0);
	}
	return (printed);
}

static void	ftoa_flag(char *s, long double n, t_frmt *prm, int flags, int size)
{
	int precision;
	int prefix;
	int len;

	precision = prm->precision;
	n = round_f(n, precision);
	if (precision || flags & F_HASH)
		precision++;
	prefix = (n < 0 || flags & (F_PLUS | F_SPACE));
	len = ((int)n ? prm->len : 1);
	if (flags & F_MINUS)
	{
		if ((int)n)
			ntoa(s + len + prefix, n);
		else
			*(s + len + prefix - 1) = '0';
		fracttoa(s + len + prefix, n, precision);
		return ;
	}
	s += size;
	if (!(flags & F_ZERO))
		prefix_fe(s - len - precision - prefix, n, flags);
	if ((int)n)
		ntoa(s - precision, n);
	else
		*(s - precision - 1) = '0';
	fracttoa(s - precision, n, precision);
}

int			print_f(long double n, t_frmt *prm)
{
	char	*out;
	int		prefix;
	int		size;
	int		flags;
	int		printed;
	int		precision;

	flags = prm->flags;
	precision = (prm->precision ? prm->precision + 1 : 0);
	prefix = (n < 0 || flags & (F_PLUS | F_SPACE));
	size = prm->len + precision + prefix;
	size = MAX(size, prm->width);
	if (!(out = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(out, (flags & F_ZERO ? '0' : ' '), size);
	*(out + size) = 0;
	ftoa_flag(out, n, prm, flags, size);
	if (flags & (F_ZERO | F_MINUS))
		prefix_fe(out, n, flags);
	printed = 0;
	if ((prm->spec == 'g' || prm->spec == 'G') && precision > 0)
		printed += trim_zeros(out + size - 1, (prm->width >= size), prm);
	printed += write(prm->fd, out, size);
	free(out);
	return (printed);
}
