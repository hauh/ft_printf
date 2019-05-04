/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:32:54 by smorty            #+#    #+#             */
/*   Updated: 2019/04/13 18:04:28 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char const *src, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (dst[i] && (i < n))
		i++;
	while (src[j])
	{
		if (i + j + 1 < n)
		{
			dst[i + j] = src[j];
			dst[i + j + 1] = '\0';
		}
		j++;
	}
	return (i + j);
}
