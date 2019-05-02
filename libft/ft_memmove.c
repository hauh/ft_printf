/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:35:37 by smorty            #+#    #+#             */
/*   Updated: 2019/04/13 21:31:58 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void const *src, size_t n)
{
	size_t i;

	if (dst || src)
	{
		if (src <= dst)
			while (n)
			{
				n--;
				*(unsigned char *)(dst + n) = *(unsigned char *)(src + n);
			}
		else
		{
			i = 0;
			while (i < n)
			{
				*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
				i++;
			}
		}
	}
	return (dst);
}
