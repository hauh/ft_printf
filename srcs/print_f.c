/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 15:53:23 by smorty            #+#    #+#             */
/*   Updated: 2019/05/13 21:57:17 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	trim_zeros_left(char *s, int width)
{
	int printed;

	while (*s == ' ' || *s == '0')
	{
		*s = 0;
		s--;
		width++;
	}
	if (*s == '.')
	{
		*s = 0;
		s--;
		width++;
	}
	while (width > 0)
	{
		s++;
		*s = ' ';
		width--;
	}
}

static int	trim_zeros_right(char *s, int width, t_frmt *prm)
{
	int printed;

	while (*s == '0')
	{
		*s = 0;
		s--;
		width++;
	}
	if (*s == '.')
	{
		*s = 0;
		s--;
		width++;
	}
	printed = 0;
	while (width > 0)
	{
		printed += write(prm->fd, (prm->flags & F_ZERO ? "0" : " "), 1);
		width--;
	}
	return (printed);
}

static void	ftoa(char *s, long double n, int e)
{
	long double d;

	d = 1;
	while (e > 0)
	{
		d *= 10;
		e--;
	}
	while (d > 1)
	{
		d /= 10;
		*s = (int)(n / d) + '0';
		n -= (int)(n / d) * d;
		s++;
	}
	if (e <= 0)
		*s = (int)n + '0';
}

static void	ftoa_flag(char *s, long double n, t_frmt *prm, int size)
{
	int precision;
	int prefix;
	int len;

	precision = prm->precision;
	prefix = (n < 0 || prm->flags & (F_PLUS | F_SPACE));
	len = prm->len;
	if (prm->flags & F_MINUS)
	{
		ftoa(s + prefix, n, len);
		fracttoa(s + len + prefix, n, precision);
	}
	else
	{
		s += size;
		if (!(prm->flags & F_ZERO))
			prefix_fe(s - len - precision - prefix, n, prm->flags);
		ftoa(s - precision - len, n, len);
		fracttoa(s - precision, n, precision);
	}
}

int			print_f(long double n, t_frmt *prm)
{
	char	*out;
	int		prefix;
	int		size;
	int		printed;
	int		precision;

	precision = prm->precision;
	prefix = (n < 0 || prm->flags & (F_PLUS | F_SPACE));
	size = prm->len + precision + prefix;
	size = MAX(size, prm->width);
	if (!(out = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(out, (prm->flags & F_ZERO ? '0' : ' '), size);
	ftoa_flag(out, n, prm, size);
	if (prm->flags & (F_ZERO | F_MINUS))
		prefix_fe(out, n, prm->flags);
	printed = 0;
	if ((prm->spec == 'g' || prm->spec == 'G') && precision > 0 && !(prm->flags & F_HASH))
	{
		if (prm->flags & F_MINUS)
			trim_zeros_left(out + size - 1, prm->width - size);
		else
			printed += trim_zeros_right(out + size - 1, prm->width - size, prm);
	}
	printed += write(prm->fd, out, size);
	free(out);
	return (printed);
}
