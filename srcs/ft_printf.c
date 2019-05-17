/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:55:41 by smorty            #+#    #+#             */
/*   Updated: 2019/05/17 16:26:29 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	g_buf[BUFF_SIZE];
int		g_len;
int		g_printed;
int		g_error;

void error(void)
{
	g_error = -1;
}

void print_buf(void)
{
	g_printed += write(1, g_buf, g_len);
	ft_bzero(g_buf, BUFF_SIZE);
	g_len = 0;
}

int		ft_printf(const char *format, ...)
{
	va_list argp;

	g_printed = 0;
	g_error = 0;
	g_len = 0;
	if (format)
	{
		va_start(argp, format);
		while (*format)
		{
			if (*format == '%')
			{
				++format;
				if (*format == '%')
				{
					*(g_buf + g_len) = '%';
					++g_len;
					if (g_len == BUFF_SIZE)
						print_buf();
				}
				else
					parse_format(&format, argp);
			}
			else
			{
				*(g_buf + g_len) = *format;
				++g_len;
				if (g_len == BUFF_SIZE)
					print_buf();
			}
			++format;
		}
		va_end(argp);
		print_buf();
	}
	return (g_error ? g_error : g_printed);
}
