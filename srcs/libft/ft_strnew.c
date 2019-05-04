/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:09:05 by smorty            #+#    #+#             */
/*   Updated: 2019/04/13 19:12:06 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *fresh;

	fresh = (char *)malloc(sizeof(char) * (size + 1));
	if (!fresh)
		return (NULL);
	ft_bzero(fresh, size + 1);
	return (fresh);
}
