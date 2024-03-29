/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:18:07 by smorty            #+#    #+#             */
/*   Updated: 2019/11/18 22:27:25 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 != s2)
	{
		if (!s1 || !s2)
			return (0);
		while ((*s1 || *s2) && n)
		{
			if (*s1 != *s2)
				return (0);
			++s1;
			++s2;
			--n;
		}
	}
	return (1);
}
