/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:26:11 by smorty            #+#    #+#             */
/*   Updated: 2019/05/06 21:26:25 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		find_max(int a, int b, int c)
{
	if (a >= b && a >= c)
		return (a);
	if (b >= a && b >= c)
		return (b);
	return (c);
}

int		prefix_di(char *s, intmax_t n, t_frmt *params)
{
	if (n < 0)
	{
		*s = '-';
		return (1);
	}
	if ((*params).plus)
	{
		*s = '+';
		return (1);
	}
	if ((*params).space)
	{
		*s = ' ';
		return (1);
	}
	return (0);
}

int		prefix_uox(char *s, uintmax_t n, t_frmt *params)
{
	if ((*params).hash && (*params).spec != 'u' && (*params).spec != 'U' && (n || (*params).spec == 'o'))
	{
		*s = '0';
		if ((*params).spec == 'x')
		{
			*(s + 1) = 'x';
			return (2);
		}
		else if ((*params).spec == 'X')
		{	
			*(s + 1) = 'X';
			return (2);
		}
		return (1);
	}
	return (0);
}