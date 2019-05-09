/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:57:07 by smorty            #+#    #+#             */
/*   Updated: 2019/05/09 17:34:03 by smorty           ###   ########.fr       */
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

static void	utoa_flags(char *s, uintmax_t n, t_frmt *params, int flags, int size)
{
	int precision;
	int len;

	precision = (*params).precision - (flags & F_PREC);
	len = num_len_base(n, 10);
	if (flags & F_MINUS)
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

int			print_u(uintmax_t n, t_frmt *params)
{
	char	*s;
	int		size;
	int		printed;
	int		precision;
	int		flags;

	flags = (*params).flags;
	if (flags & F_ZERO && (flags & F_MINUS || flags & F_PREC))
		flags ^= F_ZERO;
	precision = (*params).precision - (flags & F_PREC);
	size = MAX(MAX(num_len_base(n, 10), precision), (*params).width);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	*(s + size) = 0;
	if (n || precision)
		utoa_flags(s, n, params, flags, size);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
