/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:49:39 by smorty            #+#    #+#             */
/*   Updated: 2019/05/09 22:58:22 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void unicode(wchar_t c, char *code)
{
    if (c <= 0x7F)
	{
        code[0] = (c & 0x7F);
		code[1] = 0;
	}
	else if (c <= 0x7FF)
	{
        code[1] = 0x80 | (c & 0x3F);
		c = (c >> 6);
        code[0] = 0xC0 | (c & 0x1F);
		code[2] = 0;
 	}
	else if (c <= 0xFFFF)
	{
        code[2] = 0x80 | (c & 0x3F);
		c = (c >> 6);
        code[1] = 0x80 | (c & 0x3F);
		c = (c >> 6);
        code[0] = 0xE0 | (c & 0xF);
		code[3] = 0;
    }
	else if (c <= 0x10FFFF)
	{
        code[3] = 0x80 | (c & 0x3F);
		c = (c >> 6);
        code[2] = 0x80 | (c & 0x3F);
		c = (c >> 6);
        code[1] = 0x80 | (c & 0x3F);
		c = (c >> 6);
        code[0] = 0xF0 | (c & 0x7);
		code[4] = 0;
    }
	else
	{
        code[2] = 0xEF;
		code[1] = 0xBF;
		code[0] = 0xBD;
		code[3] = 0;
    }
}

static int putchar_unicode(wchar_t argc)
{
	char c[5];

	if (argc > 128)
	{
		unicode(argc, &c[0]);
		if (write(1, c, 2))
			return (1);
		return (0);
	}
	else
		return(write(1, &argc, 1));	
}

int print_c(const wchar_t argc, t_frmt *params)
{
	char	*s;
	char	c[5];
	int		printed;
	int		size;
	int		flags;

	flags = (*params).flags;
	if (flags & F_ZERO && flags & F_MINUS)
		flags ^= F_ZERO;
	size = (*params).width - 1;
	if (size < 0)
		return (putchar_unicode(argc));
	if (!(s = (char *)malloc(sizeof(char) * size)))
		return (-1);
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	if (flags & F_MINUS)
		printed = putchar_unicode(argc) + write(1, s, size);
	else
		printed = write(1, s, size) + putchar_unicode(argc);
	free(s);
	return (printed);
}

int	print_s(const char *args, t_frmt *params)
{
	char	*s;
	int		printed;
	int		size;
	int		len;
	int		flags;

	flags = (*params).flags;
	if (!args)
		args = "(null)";
	if (flags & F_ZERO && flags & F_MINUS)
		flags ^= F_ZERO;
	len = ft_strlen(args);
	if (flags & F_PREC)
		len = MIN((*params).precision - (flags & F_PREC), len);
	size = MAX((*params).width, len);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	*(s + size) = 0;
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	if (flags & F_MINUS)
		ft_strncpy(s, args, len);
	else
		ft_strncpy(s + size - len, args, len);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
