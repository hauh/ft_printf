/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:27:53 by smorty            #+#    #+#             */
/*   Updated: 2019/05/07 21:32:43 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_d(intmax_t n)
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

static void	dtoa(char *s, intmax_t n)
{
	if (n < 0)
	{
		s--;
		*s = n % 10 * -1 + '0';
		n /= 10;
		n *= -1;
	}
	while (n)
	{
		s--;
		*s = n % 10 + '0';
		n /= 10;
	}
}

static void	prefix_d(char *s, intmax_t n, t_frmt *params)
{
	if (n < 0)
		*s = '-';
	else if ((*params).plus)
		*s = '+';
	else if ((*params).space)
		*s = ' ';
}

static void	ntoa_flag(char *s, intmax_t n, t_frmt *params, int size)
{
	int precision;
	int prf;
	int len;

	precision = ((*params).precision > 0 ? (*params).precision : 1);
	prf = (n < 0 || (*params).plus || (*params).space);
	len = num_len_d(n);
	if ((*params).minus)
	{
		if (precision > len)
		{
			ft_memset(s + prf, '0', precision - len);
			dtoa(s + precision + prf, n);
		}
		else
			dtoa(s + len + prf, n);
		prefix_d(s, n, params);
	}
	else
	{
		s += size;
		if (precision > len)
			ft_memset(s - precision, '0', precision - len);
		dtoa(s, n);
		if (!(*params).zero)
			prefix_d(s - (precision > len ? precision : len) - prf, n, params);
	}
}

int			print_d(intmax_t n, t_frmt *params)
{
	char	*s;
	int		prefix;
	int		size;
	int		printed;
	int		precision;

	if ((*params).zero && ((*params).minus || (*params).precision >= 0))
		(*params).zero = 0;
	precision = (*params).precision;
	prefix = (n < 0 || (*params).plus || (*params).space);
	size = (!n && precision ? 1 : num_len_d(n)) + prefix;
	size = find_max(size, (*params).width, precision + prefix);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, ((*params).zero ? '0' : ' '), size);
	*(s + size) = 0;
	if (n || precision)
		ntoa_flag(s, n, params, size);
	if ((*params).zero)
		prefix_d(s, n, params);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
