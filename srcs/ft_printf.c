/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:55:41 by smorty            #+#    #+#             */
/*   Updated: 2019/05/19 23:11:58 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	g_buf[BUFF_SIZE];
int		g_len;
int		g_printed;
int		g_error;

static t_frmt	initialize_params(void)
{
	t_frmt prm;

	prm.flags = 0;
	prm.mod = 0;
	prm.width = 0;
	prm.precision = 1;
	prm.spec = 0;
	prm.fd = 1;
	return (prm);
}

static void		parse_string(const char **format, va_list argp)
{
	while (**format)
	{
		if (**format == '%')
		{
			++(*format);
			if (**format == '%')
			{
				char_to_buf('%');
				++(*format);
			}
			else if (**format)
				parse_params(format, argp, initialize_params());
		}
		else if (**format == '{')
			check_color(format);
		else
		{
			char_to_buf(**format);
			++(*format);
		}
	}
}

int				ft_printf(const char *format, ...)
{
	va_list argp;

	g_printed = 0;
	g_error = 0;
	if (format)
	{
		g_len = 0;
		va_start(argp, format);
		parse_string(&format, argp);
		va_end(argp);
		print_buf();
		ft_bzero(g_buf, BUFF_SIZE);
	}
	return (g_error ? g_error : g_printed);
}
