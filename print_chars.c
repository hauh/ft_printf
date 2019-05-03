/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:49:39 by smorty            #+#    #+#             */
/*   Updated: 2019/05/03 23:02:20 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_character(const char c, t_frmt params)
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

static int	print_string(const char *s, t_frmt params)
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

int			print_chars(void *argp, t_frmt params)
{
	if (params.spec == 's')
		return (print_string((const char *)argp, params));
	if (params.spec == 'c')
		return (print_character((const char)argp, params));
	return (print_character(*(const char *)argp, params));
}
