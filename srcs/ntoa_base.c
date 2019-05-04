/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:27:53 by smorty            #+#    #+#             */
/*   Updated: 2019/05/04 18:15:51 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int num_len(long long n, int base)
{
	int size;

	if (!n)
		return (1);
	size = (n < 0 ? 1 : 0);
	while (n)
	{
		n = n / base;
		size++;
	}
	return (size);
}

static int num_len_u(unsigned long long n, int base)
{
	int size;

	if (!n)
		return (1);
	size = 0;
	while (n)
	{
		n = n / base;
		size++;
	}
	return (size);
}

char *ntoa_base(long long n, int base, t_frmt *params)
{
	int		size;
	char	*s;

	size = num_len(n, base);
	s = (char *)malloc(sizeof(char) * (size + 1));
	if (!s)
		return (NULL);
	s[size] = 0;
	if (n < 0)
		*s = -1;
	if (!n)
		*s = '0';
	while (n)
	{
		size--;
		s[size] = (n < 0 ? (n % base) * -1 + '0' : n % base + '0');
		if (s[size] > '9')
			s[size] += ((*params).spec == 'x' ? 39 : 7);
		n /= base;
		(*params).width--;
		(*params).precision--;
	}
	return (s);
}

char *ntoa_base_u(unsigned long long n, int base, t_frmt *params)
{
	int		size;
	char	*s;

	size = num_len_u(n, base);
	s = (char *)malloc(sizeof(char) * (size + 1));
	if (!s)
		return (NULL);
	s[size] = 0;
	while (size)
	{
		size--;
		s[size] = n % base + '0';
		if (s[size] > '9')
			s[size] += ((*params).spec == 'x' ? 39 : 7);
		n /= base;
		(*params).width--;
		(*params).precision--;
	}
	return (s);
}