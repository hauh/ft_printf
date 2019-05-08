/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:41:22 by smorty            #+#    #+#             */
/*   Updated: 2019/05/08 17:51:15 by smorty           ###   ########.fr       */
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

static void	xtoa(char *s, uintmax_t n, int spec)
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

	precision = (*params).precision - (*params).flag_prec;
	hash = ((*params).hash ? 2 : 0);
	len = num_len_x(n);
	if ((*params).minus)
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
	if (!(*params).zero)
		prefix_x(s - (precision > len ? precision : len) - hash, n, params);
}

int			print_x(uintmax_t n, t_frmt *params)
{
	char	*s;
	int		size;
	int		hash;
	int		printed;
	int		precision;

	if ((*params).zero && ((*params).minus || (*params).flag_prec))
		(*params).zero = 0;
	precision = (*params).precision - (*params).flag_prec;
	hash = (*params).hash;
	size = MAX(num_len_x(n), precision);
	if ((n && hash && precision) || hash == 2)
		size += 2;
	size = MAX(size, (*params).width);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, ((*params).zero ? '0' : ' '), size);
	*(s + size) = 0;
	if (n || precision || hash == 2)
		xtoa_flag(s, n, params, size);
	if ((*params).zero && (n || hash == 2))
		prefix_x(s, n, params);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
