/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:03:03 by smorty            #+#    #+#             */
/*   Updated: 2019/04/13 18:19:14 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	char *s0;

	s0 = (char *)s;
	while (*s)
		s++;
	if (!c)
		return ((char *)s);
	while (s != s0)
	{
		s--;
		if (*s == (char)c)
			return ((char *)s);
	}
	return (NULL);
}
