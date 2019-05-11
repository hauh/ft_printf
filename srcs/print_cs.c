/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:49:39 by smorty            #+#    #+#             */
/*   Updated: 2019/05/11 22:10:32 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int unicode(wchar_t c, char *code)
{
	if (c <= 0x7F)
	{
		*code = (c & 0x7F);
		return (1);
	}
	else if (c <= 0x7FF)
	{
		*(code + 1) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*code = 0xC0 | (c & 0x1F);
		return (2);
	}
	else if (c <= 0xFFFF)
	{
		*(code + 2) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*(code + 1) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*code = 0xE0 | (c & 0xF);
		return (3);
	}
	if (c <= 0x10FFFF)
	{
		*(code + 3) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*(code + 2) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*(code + 1) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*code = 0xF0 | (c & 0x7);
		return (4);
	}
	return (0);
}

static int putchar_unicode(wchar_t argch)
{
	char code[4];

	if (argch <= 0x7F)
		return(write(1, &argch, 1));
	if (argch <= 0x7FF)
		return (write(1, code, unicode(argch, &code[0])));
	else if (argch <= 0xFFFF)
		return (write(1, code, unicode(argch, &code[0])));
	else
		return (write(1, code, unicode(argch, &code[0])));
	return (0);
}

int print_c(const wchar_t argch, t_frmt *params)
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
		return (putchar_unicode(argch));
	if (!(s = (char *)malloc(sizeof(char) * size)))
		return (-1);
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	if (flags & F_MINUS)
		printed = putchar_unicode(argch) + write(1, s, size);
	else
		printed = write(1, s, size) + putchar_unicode(argch);
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
	if ((flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		flags ^= F_ZERO;
	len = ft_strlen(args);
	if (flags & F_PREC)
		len = MIN((*params).precision - (flags & F_PREC), len);
	size = MAX((*params).width, len);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	if (flags & F_MINUS)
		ft_strncpy(s, args, len);
	else
		ft_strncpy(s + size - len, args, len);
	printed = write(1, s, size);
	free(s);
	return (printed);
}

int	print_ws(const wchar_t *args, t_frmt *params)
{
	char	*s;
	int		printed;
	int		size;
	int		flags;
	int		len;
	int		n;

	flags = (*params).flags;
	if (!args)
		return (print_s("(null)", params));
	if ((flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		flags ^= F_ZERO;
	len = lensize(args);
	if (flags & F_PREC)
		len = MIN((*params).precision - (flags & F_PREC), len);
	size = MAX((*params).width, len);
	if (!(s = (char *)malloc(sizeof(char) * (size + 4))))
		return (-1);
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	printed = 0;
	n = 0;
	if (flags & F_MINUS)
	{
		while (n < len && *args)
		{
			n += unicode(*args, s + n);
			args++;
		}
		if (n > len)
			size -= n - len;
	}
	else
	{
		while (len > 0 && *args)
		{
			n = unicode(*args, s + size - len);
			len -= n;
			args++;
		}
		if (len < 0)
			while (len + n > 0)
			{
				if ((*params).width)
					printed += write(1, (flags & F_ZERO ? "0" : " "), 1);
				n--;
				size--;
			}
	}
	printed += write(1, s, size);
	free(s);
	return (printed);
}
