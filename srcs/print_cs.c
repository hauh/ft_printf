/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:49:39 by smorty            #+#    #+#             */
/*   Updated: 2019/05/06 15:12:47 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(const char c, t_frmt *params)
{
	int		printed;
	char	fill;	printed = 0;
	(*params).width--;
	if ((*params).minus)
	{
		printed += write(1, &c, 1);
		while ((*params).width > 0)
		{
			printed += write(1, " ", 1);
			(*params).width--;
		}
	}
	else
	{
		fill = ((*params).zero ? '0' : ' ');
		while ((*params).width > 0)
		{
			printed += write(1, &fill, 1);
			(*params).width--;
		}
		printed += write(1, &c, 1);
	}
	return (printed);
}

int	print_string(const char *s, t_frmt *params)
{
	int		printed;
	char	fill;
	int		len;

	if (!s)
		return(write(1, "(null)", 6));
	printed = 0;
	len = ft_strlen(s);
	if ((*params).precision >= 0 && (*params).precision < len)
		len = (*params).precision;
	(*params).width -= len;
	if ((*params).minus)
	{
		printed += write(1, s, len);
		while ((*params).width > 0)
		{
			printed += write(1, " ", 1);
			(*params).width--;
		}
	}
	else
	{
		fill = ((*params).zero ? '0' : ' ');
		while ((*params).width > 0)
		{
			printed += write(1, &fill, 1);
			(*params).width--;
		}
		printed += write(1, s, len);
	}
	return (printed);
}
