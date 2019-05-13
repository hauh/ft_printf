/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:57:07 by smorty            #+#    #+#             */
/*   Updated: 2019/05/13 16:11:48 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int			print_u(uintmax_t n, t_frmt *prm)
{
	char	*s;
	int		size;
	int		printed;
	int		precision;

	if (prm->flags & F_ZERO && (prm->flags & (F_MINUS | F_PREC)))
		prm->flags ^= F_ZERO;
	precision = prm->precision - (prm->flags & F_PREC);
	prm->len = num_len_base(n, 10);
	size = MAX(MAX(prm->len, precision), prm->width);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, (prm->flags & F_ZERO ? '0' : ' '), size);
	if (n || precision)
		utoa_flags(s, n, prm, size);
	printed = write(prm->fd, s, size);
	free(s);
	return (printed);
}
