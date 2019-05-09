/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:25:04 by smorty            #+#    #+#             */
/*   Updated: 2019/05/09 17:45:58 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		num_len(intmax_t n)
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

int		num_len_base(uintmax_t n, int base)
{
	int size;

	size = 0;
	while (n)
	{
		n = n / base;
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