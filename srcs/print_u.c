/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:57:07 by smorty            #+#    #+#             */
/*   Updated: 2019/05/07 19:33:21 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_u(uintmax_t n)
{
	int size;

	size = 0;
	while (n)
	{
		n = n / 10;
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

static void	utoa_flags(char *s, uintmax_t n, t_frmt *params, int size)
{
	int precision;
	int len;

	precision = ((*params).precision > 0 ? (*params).precision : 1);
	len = num_len_u(n);
	if ((*params).minus)
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

	if ((*params).zero && ((*params).minus || (*params).precision >= 0))
		(*params).zero = 0;
	precision = (*params).precision;
	size = (!n && precision ? 1 : num_len_u(n));
	size = find_max(size, (*params).width, precision);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, ((*params).zero ? '0' : ' '), size);
	*(s + size) = 0;
	if (n || precision)
		utoa_flags(s, n, params, size);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
