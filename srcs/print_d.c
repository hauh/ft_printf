/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:27:53 by smorty            #+#    #+#             */
/*   Updated: 2019/05/13 16:15:38 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	prefix_d(char *s, intmax_t n, int flags)
{
	if (n < 0)
		*s = '-';
	else if (flags & F_PLUS)
		*s = '+';
	else if (flags & F_SPACE)
		*s = ' ';
}

static void	dtoa_flag(char *s, intmax_t n, t_frmt *prm, int flags, int size)
{
	int precision;
	int prefix;
	int len;

	precision = prm->precision - (flags & F_PREC);
	prefix = (n < 0 || flags & F_PLUS || flags & F_SPACE);
	len = num_len(n);
	if (flags & F_MINUS)
	{
		if (precision > len)
		{
			ft_memset(s + prefix, '0', precision - len);
			ntoa(s + precision + prefix, n);
		}
		else
			ntoa(s + len + prefix, n);
		prefix_d(s, n, flags);
		return ;
	}
	s += size;
	if (precision > len)
		ft_memset(s - precision, '0', precision - len);
	ntoa(s, n);
	if (!(flags & F_ZERO))
		prefix_d(s - (precision > len ? precision : len) - prefix, n, flags);
}

int			print_d(intmax_t n, t_frmt *prm)
{
	char	*s;
	int		prefix;
	int		size;
	int		flags;
	int		printed;
	int		precision;

	flags = prm->flags;
	if (flags & F_ZERO && flags & (F_MINUS | F_PREC))
		flags ^= F_ZERO;
	precision = prm->precision - (flags & F_PREC);
	prefix = (precision && (n < 0 || flags & F_PLUS || flags & F_SPACE));
	size = MAX(num_len(n), precision) + prefix;
	size = MAX(size, prm->width);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	*(s + size) = 0;
	if (n || precision)
		dtoa_flag(s, n, prm, flags, size);
	if (flags & F_ZERO)
		prefix_d(s, n, flags);
	printed = write(prm->fd, s, size);
	free(s);
	return (printed);
}
