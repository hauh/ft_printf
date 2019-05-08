/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:58:45 by smorty            #+#    #+#             */
/*   Updated: 2019/05/07 19:33:36 by smorty           ###   ########.fr       */
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

static void	otoa_flag(char *s, uintmax_t n, t_frmt *params, int size)
{
	int precision;
	int len;
	int hash;

	precision = ((*params).precision > 0 ? (*params).precision : 1);
	hash = (*params).hash;
	len = num_len_o(n);
	if ((*params).minus)
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
	int		hash;
	int		printed;
	int		precision;

	if ((*params).zero && ((*params).minus || (*params).precision >= 0))
		(*params).zero = 0;
	precision = (*params).precision;
	hash = (*params).hash;
	size = (!n && precision ? 1 : num_len_o(n) + hash);
	size = find_max(size, (*params).width, precision + hash);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, ((*params).zero ? '0' : ' '), size);
	*(s + size) = 0;
	if (n || precision || hash)
		otoa_flag(s, n, params, size);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
