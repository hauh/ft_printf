/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:58:06 by smorty            #+#    #+#             */
/*   Updated: 2019/04/13 19:27:35 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*fresh;

	if (!s || !f)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	fresh = (char *)malloc(sizeof(char) * (i + 1));
	if (!fresh)
		return (NULL);
	fresh[i] = '\0';
	while (i)
	{
		i--;
		fresh[i] = f(i, s[i]);
	}
	return (fresh);
}
