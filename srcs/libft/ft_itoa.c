/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:10:42 by smorty            #+#    #+#             */
/*   Updated: 2019/04/10 20:48:17 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	unsigned int	size;
	long			tmp;
	char			*fresh;

	size = (n <= 0) ? 1 : 0;
	tmp = n;
	while (n)
	{
		n /= 10;
		size++;
	}
	fresh = (char *)malloc(sizeof(char) * (size + 1));
	if (!fresh)
		return (NULL);
	fresh[size] = '\0';
	fresh[0] = (tmp >= 0) ? '0' : '-';
	if (tmp < 0)
		tmp *= -1;
	while (tmp)
	{
		size--;
		fresh[size] = tmp % 10 + '0';
		tmp /= 10;
	}
	return (fresh);
}
