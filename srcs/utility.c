/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:25:04 by smorty            #+#    #+#             */
/*   Updated: 2019/05/13 15:33:47 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		num_len(intmax_t n)
{
	intmax_t	d;
	int			size;

	if (!n)
		return (0);
	size = 1;
	n /= (n < 0 ? -10 : 10);
	d = 1;
	while (d <= n)
	{
		d *= 10;
		size++;
	}
	return (size);
}

int		num_len_base(uintmax_t n, int base)
{
	uintmax_t	d;
	int			size;

	if (!n)
		return (0);
	size = 1;
	n /= base;
	d = 1;
	while (d <= n)
	{
		d *= base;
		size++;
	}
	return (size);
}

void	ntoa(char *s, intmax_t n)
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

int lensize(const wchar_t *s)
{
	int size;

	size = 0;
	while (*s)
	{
		if (*s <= 0x7F)
			size++;
		else if (*s <= 0x7FF)
			size += 2;
		else if (*s <= 0xFFFF)
			size += 3;
		else
			size += 4;
		s++;
	}
	return (size);
}

