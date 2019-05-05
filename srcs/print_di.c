/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:27:53 by smorty            #+#    #+#             */
/*   Updated: 2019/05/05 21:57:28 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		num_len(intmax_t n, int precision)
{
	int size;

	if (!n && precision < 0)
		return (1);
	size = 0;
	while (n)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void		ntoa(char *s, intmax_t n, t_frmt params)
{
	if (!n && params.precision < 0)
		*(s - 1) = '0';
	else
	{
		while (n)
		{
			s--;
			*s = (n < 0 ? (n % 10) * -1 + '0' : n % 10 + '0');
			if (*s > '9')
				*s += (params.spec == 'x' ? 39 : 7);
			n /= 10;
		}
	}
}

static void		ntoa_flag_minus(char *s, intmax_t n, t_frmt params)
{
	int len;

	len = num_len(n, params.precision);
	s += prefix_di(s, n, params);
	if (params.precision >= len)
	{
		ft_memset(s, '0', params.precision);
		ntoa(s + params.precision, n, params);
	}
	else
		ntoa(s + len, n, params);
}

static void		ntoa_no_flag_minus(char *s, intmax_t n, t_frmt params)
{
	int len;

	len = num_len(n, params.precision);
	if (params.precision >= len)
	{
		ft_memset(s - params.precision, '0', params.precision);
		prefix_di(s - params.precision - 1, n, params);
	}
	else if (!params.zero)
		prefix_di(s - len - 1, n, params);
	ntoa(s, n, params);
}

int				print_integer(intmax_t n, t_frmt params)
{
	char	*s;
	char	pref;
	int		size;
	int		printed;

	if (params.minus || params.precision >= 0)
		params.zero = 0;
	pref = (n < 0 || params.plus || params.space);
	size = num_len(n, params.precision);
	size = find_max(size + pref, params.width, params.precision + pref);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, (params.zero ? '0' : ' '), size);
	*(s + size) = 0;
	if (params.minus)
		ntoa_flag_minus(s, n, params);
	else
		ntoa_no_flag_minus(s + size, n, params);
	if (params.zero)
		prefix_di(s, n, params);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
