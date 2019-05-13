/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:58:45 by smorty            #+#    #+#             */
/*   Updated: 2019/05/13 16:06:44 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	otoa(char *s, uintmax_t n, int hash)
{
	while (n)
	{
		s--;
		*s = n % 8 + '0';
		n /= 8;
	}
	if (hash)
		*(s - 1) = '0';
}

static void	otoa_flag(char *s, uintmax_t n, t_frmt *prm, int size)
{
	int precision;
	int len;
	int hash;

	precision = prm->precision - (prm->flags & F_PREC);
	hash = (prm->flags & F_HASH ? 1 : 0);
	len = prm->len;
	if (prm->flags & F_MINUS)
	{
		if (precision > len)
		{
			ft_memset(s, '0', precision - len);
			otoa(s + precision, n, hash);
		}
		else
			otoa(s + len + hash, n, hash);
	}
	else
	{
		s += size;
		if (precision > len)
			ft_memset(s - precision, '0', precision - len);
		otoa(s, n, hash);
	}
}

int			print_o(uintmax_t n, t_frmt *prm)
{
	char	*s;
	int		size;
	int		printed;
	int		precision;

	if (prm->flags & F_ZERO && prm->flags & (F_MINUS | F_PREC))
		prm->flags ^= F_ZERO;
	precision = prm->precision - (prm->flags & F_PREC);
	prm->len = num_len_base(n, 8);
	size = MAX(prm->len + (prm->flags & F_HASH ? 1 : 0), precision);
	size = MAX(size, prm->width);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, (prm->flags & F_ZERO ? '0' : ' '), size);
	if (n || precision || prm->flags & F_HASH)
		otoa_flag(s, n, prm, size);
	printed = write(prm->fd, s, size);
	free(s);
	return (printed);
}
