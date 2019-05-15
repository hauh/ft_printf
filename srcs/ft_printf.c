/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:55:41 by smorty            #+#    #+#             */
/*   Updated: 2019/05/15 17:27:49 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*g_buf;
int		g_len;
int		g_printed;
int		g_error;

void error(void)
{
	free(g_buf);
	g_error = -1;
}

void print_buf(void)
{
	g_printed += write(1, g_buf, g_len);
	g_len = 0;
}

int		ft_printf(const char *format, ...)
{
	va_list argp;

	g_printed = 0;
	if (format)
	{
		g_buf = (char *)malloc(sizeof(char) * BUFF_SIZE);
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
		free(g_buf);
	}
	return (g_error ? g_error : g_printed);
}
