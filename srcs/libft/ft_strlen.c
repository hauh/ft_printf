/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 20:55:27 by smorty            #+#    #+#             */
/*   Updated: 2019/11/18 22:26:58 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"

size_t	ft_strlen(const char *s)
{
	const char *s0;

	s0 = s;
	while (*s)
		++s;
	return (s - s0);
}
