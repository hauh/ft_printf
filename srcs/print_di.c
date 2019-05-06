/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:27:53 by smorty            #+#    #+#             */
/*   Updated: 2019/05/06 23:21:20 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_di(intmax_t n)
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

static void	ntoa(char *s, intmax_t n)
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

static void prefix_di(char *s, intmax_t n, t_frmt *params)
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
	int prefix;
	int len;

	precision = (*params).precision;
	prefix = (n < 0 || (*params).plus || (*params).space);
	len = num_len_di(n);
	if ((*params).minus)
	{
		if (precision > len)
		{
			ft_memset(s + prefix, '0', precision - len);
			ntoa(s + precision + prefix, n);
		}
		else
			ntoa(s + len + prefix, n);
		prefix_di(s, n, params);
	}
	else
	{
		s += size;
		if (precision > len)
			ft_memset(s - precision, '0', precision - len);
		ntoa(s, n);
		if (!(*params).zero)
			prefix_di(s - (precision > len ? precision : len) - prefix, n, params);
	}
}

int			print_di(intmax_t n, t_frmt *params)
{
	char	*s;
	int		pref;
	int		size;
	int		printed;
	int		precision;

	precision = (*params).precision;
	if ((*params).minus || precision >= 0)
		(*params).zero = 0;
	pref = (n < 0 || (*params).plus || (*params).space);
	size = find_max((n && precision ? num_len_di(n) : 1) + pref, (*params).width, precision + pref);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, ((*params).zero ? '0' : ' '), size);
	*(s + size) = 0;
	if (n)
		ntoa_flag(s, n, params, size);
	else
	{
		if (precision)
		{
			*(s + size - 1) = '0';
			prefix_di(s, n, params);
		}
		while (precision > 0)
		{
			*(s + precision) = '0';
			precision--;
		}
	}
	if ((*params).zero)
		prefix_di(s, n, params);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
