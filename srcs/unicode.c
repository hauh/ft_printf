/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:34:30 by smorty            #+#    #+#             */
/*   Updated: 2019/05/21 14:58:03 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	unicode_2(wchar_t c)
{
	CHECK_BUFF(2);
	*(g_buf + g_len + 1) = 0x80 | (c & 0x3F);
	c = (c >> 6);
	*(g_buf + g_len) = 0xC0 | (c & 0x1F);
	g_len += 2;
	if (g_len == BUFF_SIZE)
		print_buf();
}

static void	unicode_3(wchar_t c)
{
	CHECK_BUFF(3);
	*(g_buf + g_len + 2) = 0x80 | (c & 0x3F);
	c = (c >> 6);
	*(g_buf + g_len + 1) = 0x80 | (c & 0x3F);
	c = (c >> 6);
	*(g_buf + g_len) = 0xE0 | (c & 0xF);
	g_len += 3;
	if (g_len == BUFF_SIZE)
		print_buf();
}

static void	unicode_4(wchar_t c)
{
	CHECK_BUFF(4);
	*(g_buf + g_len + 3) = 0x80 | (c & 0x3F);
	c = (c >> 6);
	*(g_buf + g_len + 2) = 0x80 | (c & 0x3F);
	c = (c >> 6);
	*(g_buf + g_len + 1) = 0x80 | (c & 0x3F);
	c = (c >> 6);
	*(g_buf + g_len) = 0xF0 | (c & 0x7);
	g_len += 4;
	if (g_len == BUFF_SIZE)
		print_buf();
}

int			unicode(wchar_t c)
{
	if (c <= 0x7F)
	{
		char_to_buf(c & 0x7F, 1);
		return (1);
	}
	else if (c <= 0x7FF && BUFF_SIZE >= 2)
	{
		unicode_2(c);
		return (2);
	}
	else if (c <= 0xFFFF && BUFF_SIZE >= 3)
	{
		unicode_3(c);
		return (3);
	}
	else if (BUFF_SIZE >= 4)
	{
		unicode_4(c);
		return (4);
	}
	return (0);
}
