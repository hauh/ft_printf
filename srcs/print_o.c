/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:58:45 by smorty            #+#    #+#             */
/*   Updated: 2019/05/09 19:46:14 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_o(uintmax_t n)
{
	int size;

	size = 0;
	while (n)
	{
		n = n / 8;
		size++;
	}
	return (size);
}

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

static void	otoa_flag(char *s, uintmax_t n, t_frmt *params, int flags, int size)
{
	int precision;
	int len;
	int hash;

	precision = (*params).precision - (flags & F_PREC);
	hash = (flags & F_HASH ? 1 : 0);
	len = num_len_base(n, 8);
	if (flags & F_MINUS)
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

int			print_o(uintmax_t n, t_frmt *params)
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
	size = MAX(num_len_base(n, 8) + (flags & F_HASH ? 1 : 0), precision);
	size = MAX(size, (*params).width);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	*(s + size) = 0;
	if (n || precision || flags & F_HASH)
		otoa_flag(s, n, params, flags, size);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
