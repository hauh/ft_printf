/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:41:22 by smorty            #+#    #+#             */
/*   Updated: 2019/05/13 16:09:32 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	xtoa(char *s, uintmax_t n, int spec)
{
	if (spec == 'X')
	{
		while (n)
		{
			s--;
			*s = n % 16;
			*s += (*s < 10 ? '0' : 55);
			n /= 16;
		}
	}
	else
	{
		if (spec == 'p')
			*(s + 1) = '0';
		while (n)
		{
			s--;
			*s = n % 16;
			*s += (*s < 10 ? '0' : 87);
			n /= 16;
		}
	}
}

static void	prefix_x(char *s, uintmax_t n, t_frmt *prm)
{
	if (prm->spec == 'p')
	{
		*s = '0';
		*(s + 1) = 'x';
	}
	else if (prm->flags & F_HASH && n)
	{
		*s = '0';
		*(s + 1) = prm->spec;
	}
}

static void	xtoa_flag(char *s, uintmax_t n, t_frmt *prm, int size)
{
	int precision;
	int len;
	int hash;

	precision = prm->precision - (prm->flags & F_PREC);
	hash = (prm->flags & F_HASH ? 2 : 0);
	len = prm->len;
	if (prm->flags & F_MINUS)
	{
		if (precision > len)
		{
			ft_memset(s, '0', precision - len);
			xtoa(s + precision, n, prm->spec);
		}
		else
			xtoa(s + len + hash, n, prm->spec);
		prefix_x(s, n, prm);
		return ;
	}
	s += size;
	if (precision > len)
		ft_memset(s - precision, '0', precision - len);
	xtoa(s, n, prm->spec);
	if (!(prm->flags & F_ZERO))
		prefix_x(s - (precision > len ? precision : len) - hash, n, prm);
}

int			print_x(uintmax_t n, t_frmt *prm)
{
	char	*s;
	int		size;
	int		hash;
	int		printed;
	int		precision;

	if (prm->flags & F_ZERO && prm->flags & (F_MINUS | F_PREC))
		prm->flags ^= F_ZERO;
	precision = prm->precision - (prm->flags & F_PREC);
	hash = (prm->spec == 'p' ? 2 : prm->flags & F_HASH);
	prm->len = num_len_base(n, 16);
	size = MAX(prm->len, precision);
	if ((n && hash && precision) || hash == 2)
		size += 2;
	size = MAX(size, prm->width);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, (prm->flags & F_ZERO ? '0' : ' '), size);
	if (n || precision || hash == 2)
		xtoa_flag(s, n, prm, size);
	if (prm->flags & F_ZERO && (n || hash == 2))
		prefix_x(s, n, prm);
	printed = write(prm->fd, s, size);
	free(s);
	return (printed);
}
