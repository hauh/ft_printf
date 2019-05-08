/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:41:22 by smorty            #+#    #+#             */
/*   Updated: 2019/05/07 22:05:38 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_x(uintmax_t n)
{
	int size;

	size = 0;
	while (n)
	{
		n = n / 16;
		size++;
	}
	return (size);
}

static void	xtoa(char *s, uintmax_t n, int hash, int spec)
{
	while (n)
	{
		s--;
		*s = n % 16;
		*s += (*s < 10 ? '0' : spec - 33);
		n /= 16;
	}
}

static void	prefix_x(char *s, uintmax_t n, t_frmt *params)
{
	if (((*params).hash && n) || (*params).hash == 2)
	{
		*s = '0';
		*(s + 1) = (*params).spec;
	}
}

static void	xtoa_flag(char *s, uintmax_t n, t_frmt *params, int size)
{
	int precision;
	int len;
	int hash;

	precision = ((*params).precision > 0 ? (*params).precision : 1);
	hash = ((*params).hash ? 2 : 0);
	len = num_len_x(n);
	if ((*params).minus)
	{
		if (precision > len)
		{
			ft_memset(s, '0', precision - len);
			xtoa(s + precision, n, hash, (*params).spec);
		}
		else
			xtoa(s + len + hash, n, hash, (*params).spec);
		prefix_x(s, n, params);
	}
	else
	{
		s += size;
		if (precision > len)
			ft_memset(s - precision, '0', precision - len);
		xtoa(s, n, hash, (*params).spec);
		if (!(*params).zero)
			prefix_x(s - (precision > len ? precision : len) - hash, n, params);
	}
}

int			print_x(uintmax_t n, t_frmt *params)
{
	char	*s;
	int		size;
	int		hash;
	int		printed;
	int		precision;

	if ((*params).zero && ((*params).minus || (*params).precision >= 0))
		(*params).zero = 0;
	precision = (*params).precision;
	hash = ((((*params).hash && n) || (*params).hash == 2) ? 2 : 0);
	size = ((!n && precision) ? 1 : num_len_x(n) + hash);
	size = find_max(size, (*params).width, precision + hash);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, ((*params).zero ? '0' : ' '), size);
	*(s + size) = 0;
	if (n || precision || (*params).hash == 2)
		xtoa_flag(s, n, params, size);
	if ((*params).zero && (n || (*params).hash == 2))
		prefix_x(s, n, params);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
