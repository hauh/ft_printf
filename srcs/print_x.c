/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 14:41:22 by smorty            #+#    #+#             */
/*   Updated: 2019/05/06 16:24:46 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int num_len_base(uintmax_t n, int precision, char base)
{
	int size;

	if (!n && precision < 0)
		return (1);
	size = 0;
	while (n)
	{
		n = n / base;
		size++;
	}
	return (size);
}

static void		ntoa_base(char *s, uintmax_t n, t_frmt *params, char base)
{
	if ((!n && (*params).precision < 0) || ((*params).hash && base == 8))
		*(s - 1) = '0';
	else
	{
		while (n)
		{
			s--;
			*s = n % base + '0';
			if (*s > '9')
				*s += ((*params).spec == 'x' ? 39 : 7);
			n /= base;
		}
	}
}

static void		ntoa_base_flag_minus(char *s, uintmax_t n, t_frmt *params, char base)
{
	int len;

	len = num_len_base(n, (*params).precision, base);
	s += prefix_uox(s, n, params);
	if ((*params).precision >= len)
	{
		ft_memset(s, '0', (*params).precision);
		ntoa_base(s + (*params).precision, n, params, base);
	}
	else
		ntoa_base(s + len, n, params, base);
}

static void	ntoa_base_no_flag_minus(char *s, uintmax_t n, t_frmt *params, char base)
{
	int len;

	len = num_len_base(n, (*params).precision, base);
	if ((*params).precision >= len)
	{
		ft_memset(s - (*params).precision, '0', (*params).precision);
		prefix_uox(s - ((*params).spec == 'o' ? 1 : 2) - (*params).precision, n, params);
	}
	else if (!(*params).zero)
		prefix_uox(s - len - ((*params).spec == 'o' ? 1 : 2), n, params);
	ntoa_base(s, n, params, base);
}

int		print_base(uintmax_t n, t_frmt *params, char base)
{
	char	*s;
	char	pref;
	int		size;
	int		printed;

	if ((*params).minus || (*params).precision >= 0)
		(*params).zero = 0;
	pref = (base != 10 && (*params).hash && (n || base == 8) ? 2 - ((*params).spec == 'o') : 0);
	size = num_len_base(n, (*params).precision, base);
	size = find_max(size + pref, (*params).width, (*params).precision + pref);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, ((*params).zero ? '0' : ' '), size);
	*(s + size) = 0;
	if ((*params).minus)
		ntoa_base_flag_minus(s, n, params, base);
	else
		ntoa_base_no_flag_minus(s + size, n, params, base);
	if (pref && (*params).zero)
		prefix_uox(s, n, params);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
