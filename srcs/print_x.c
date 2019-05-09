/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:41:22 by smorty            #+#    #+#             */
/*   Updated: 2019/05/09 19:43:57 by smorty           ###   ########.fr       */
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

static void	prefix_x(char *s, uintmax_t n, t_frmt *params)
{
	if ((*params).spec == 'p')
	{
		*s = '0';
		*(s + 1) = 'x';
	}
	else if ((*params).flags & F_HASH && n)
	{
		*s = '0';
		*(s + 1) = (*params).spec;
	}
}

static void	xtoa_flag(char *s, uintmax_t n, t_frmt *params, int flags, int size)
{
	int precision;
	int len;
	int hash;

	precision = (*params).precision - (flags & F_PREC);
	hash = (flags & F_HASH ? 2 : 0);
	len = num_len_base(n, 16);
	if (flags & F_MINUS)
	{
		if (precision > len)
		{
			ft_memset(s, '0', precision - len);
			xtoa(s + precision, n, (*params).spec);
		}
		else
			xtoa(s + len + hash, n, (*params).spec);
		prefix_x(s, n, params);
		return ;
	}
	s += size;
	if (precision > len)
		ft_memset(s - precision, '0', precision - len);
	xtoa(s, n, (*params).spec);
	if (!(flags & F_ZERO))
		prefix_x(s - (precision > len ? precision : len) - hash, n, params);
}

int			print_x(uintmax_t n, t_frmt *params)
{
	char	*s;
	int		size;
	int		hash;
	int		printed;
	int		precision;
	int		flags;

	flags = (*params).flags;
	if (flags & F_ZERO && flags & (F_MINUS | F_PREC))
		flags ^= F_ZERO;
	precision = (*params).precision - (flags & F_PREC);
	hash = ((*params).spec == 'p' ? 2 : flags & F_HASH);
	size = MAX(num_len_base(n, 16), precision);
	if ((n && hash && precision) || hash == 2)
		size += 2;
	size = MAX(size, (*params).width);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	*(s + size) = 0;
	if (n || precision || hash == 2)
		xtoa_flag(s, n, params, flags, size);
	if (flags & F_ZERO && (n || hash == 2))
		prefix_x(s, n, params);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
