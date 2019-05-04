/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:39:45 by smorty            #+#    #+#             */
/*   Updated: 2019/04/11 21:52:14 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;

	if (n > ft_strlen(s))
		n = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	new[n] = '\0';
	while (n)
	{
		n--;
		new[n] = s[n];
	}
	return (new);
}
