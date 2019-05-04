/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:17:58 by smorty            #+#    #+#             */
/*   Updated: 2019/04/13 17:03:49 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	void *dst0;

	dst0 = dst;
	while (n)
	{
		n--;
		*(unsigned char *)dst = *(unsigned char *)src;
		dst++;
		src++;
	}
	return (dst0);
}
