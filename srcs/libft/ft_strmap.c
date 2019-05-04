/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:51:44 by smorty            #+#    #+#             */
/*   Updated: 2019/04/13 19:22:14 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *fresh;
	char *fresh0;

	if (!s || !f)
		return (NULL);
	fresh = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!fresh)
		return (NULL);
	fresh0 = fresh;
	while (*s)
	{
		*fresh = f(*s);
		fresh++;
		s++;
	}
	*fresh = '\0';
	return (fresh0);
}
