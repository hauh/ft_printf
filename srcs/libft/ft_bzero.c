/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:55:24 by smorty            #+#    #+#             */
/*   Updated: 2019/11/18 22:27:36 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char *sc;

	sc = (unsigned char *)s;
	while (n)
	{
		--n;
		*sc = 0;
		++sc;
	}
}
