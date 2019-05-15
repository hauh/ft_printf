/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:57:07 by smorty            #+#    #+#             */
/*   Updated: 2019/05/15 21:00:07 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_u(uintmax_t n)
{
	uintmax_t	d;
	int			size;

	if (!n)
		return (0);
	size = 1;
	n /= 10;
	d = 1;
	while (d <= n)
	{
		d *= 10;
		size++;
	}
	return (size);
}

static void	utoa(char *s, uintmax_t n)
{
	while (n)
	{
		s--;
		*s = n % 10 + '0';
		n /= 10;
	}
}

static void	utoa_flags(char *s, uintmax_t n, t_frmt *prm, int size)
{
	int precision;
	int len;

	precision = prm->precision - (prm->flags & F_PREC);
	len = prm->len;
	if (prm->flags & F_MINUS)
	{
		if (precision > len)
		{
			ft_memset(s, '0', precision - len);
			utoa(s + precision, n);
		}
		else
			utoa(s + len, n);
	}
	else
	{
		s += size;
		if (precision > len)
			ft_memset(s - precision, '0', precision - len);
		utoa(s, n);
	}
}

void		print_u(uintmax_t n, t_frmt *prm)
{
	char	*out;
	int		size;
	int		precision;

	if (prm->flags & F_ZERO && (prm->flags & (F_MINUS | F_PREC)))
		prm->flags ^= F_ZERO;
	precision = prm->precision - (prm->flags & F_PREC);
	prm->len = num_len_u(n);
	size = MAX(MAX(prm->len, precision), prm->width);
	if (!(out = (char *)malloc(sizeof(char) * (size + 1))))
	{
		error();
		return ;
	}
	ft_memset(out, (prm->flags & F_ZERO ? '0' : ' '), size);
	if (n || precision)
		utoa_flags(out, n, prm, size);
	*(out + size) = 0;
	move_to_buf(out);
	free(out);
}
