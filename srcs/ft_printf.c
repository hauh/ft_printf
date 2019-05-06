/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:55:41 by smorty            #+#    #+#             */
/*   Updated: 2019/05/06 23:16:20 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	int printed;
	va_list argp;

	printed = 0;
	va_start(argp, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '%')
				printed += write(1, "%", 1);
			else
				printed += parse_format(&format, argp);
		}
		else
			printed += write(1, format, 1);
		format++;
	}
	va_end(argp);
	return (printed);
}
/*
#include <stdio.h>
int main(void)
{
	ft_printf(">%+d<\n", 0);
	printf(">%+d<\n", 0);
}*/