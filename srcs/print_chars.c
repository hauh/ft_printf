/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:49:39 by smorty            #+#    #+#             */
/*   Updated: 2019/05/04 18:13:17 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(const char c, t_frmt params)
{
	int		printed;
	char	fill;

	printed = 0;
	params.width--;
	if (params.minus)
	{
		printed += write(1, &c, 1);
		while (params.width > 0)
		{
			printed += write(1, " ", 1);
			params.width--;
		}
	}
	else
	{
		fill = (params.zero ? '0' : ' ');
		while (params.width > 0)
		{
			printed += write(1, &fill, 1);
			params.width--;
		}
		printed += write(1, &c, 1);
	}
	return (printed);
}

int	print_string(const char *s, t_frmt params)
{
	int		printed;
	char	fill;

	printed = 0;
	params.width -= ft_strlen(s);
	if (params.minus)
	{
		printed += write(1, s, ft_strlen(s));
		while (params.width > 0)
		{
			printed += write(1, " ", 1);
			params.width--;
		}
	}
	else
	{
		fill = (params.zero ? '0' : ' ');
		while (params.width > 0)
		{
			printed += write(1, &fill, 1);
			params.width--;
		}
		printed += write(1, s, ft_strlen(s));
	}
	return (printed);
}
