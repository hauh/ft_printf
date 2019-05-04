/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:55:56 by smorty            #+#    #+#             */
/*   Updated: 2019/05/01 22:05:26 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlong(long long n)
{
	long long tmp;
	long long mod;

	if (!n)
		ft_putchar('0');
	else
	{
		tmp = (n < 0 ? n / -10 : n / 10);
		mod = (n < 0 ? -1 : 1);
		if (n < 0)
			ft_putchar('-');
		while (tmp)
		{
			tmp /= 10;
			mod *= 10;
		}
		while (n)
		{
			ft_putchar(n / mod + '0');
			n %= mod;
			mod /= 10;
		}
	}
}
