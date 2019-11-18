/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 19:01:47 by smorty            #+#    #+#             */
/*   Updated: 2019/11/18 22:27:10 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char *sc;

	sc = (unsigned char *)s;
	while (n)
	{
		--n;
		*sc = (unsigned char)c;
		++sc;
	}
	return (s);
}
