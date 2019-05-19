/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:49:39 by smorty            #+#    #+#             */
/*   Updated: 2019/05/19 20:23:15 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


static int	unicode(wchar_t c)
{
	if (c <= 0x7F)
	{
		*(g_buf + g_len) = (c & 0x7F);
		++g_len;
		if (g_len == BUFF_SIZE)
			print_buf();
		return (1);
	}
	else if (c <= 0x7FF && BUFF_SIZE >= 2)
	{
		if (BUFF_SIZE - g_len < 2)
			print_buf();
		*(g_buf + g_len + 1) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*(g_buf + g_len) = 0xC0 | (c & 0x1F);
		g_len += 2;
		if (g_len == BUFF_SIZE)
			print_buf();
		return (2);
	}
	else if (c <= 0xFFFF && BUFF_SIZE >= 3)
	{
		if (BUFF_SIZE - g_len < 3)
			print_buf();
		*(g_buf + g_len + 2) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*(g_buf + g_len + 1) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*(g_buf + g_len) = 0xE0 | (c & 0xF);
		g_len += 3;
		if (g_len == BUFF_SIZE)
			print_buf();
		return (3);
	}
	else if (BUFF_SIZE >= 4)
	{
		if (BUFF_SIZE - g_len < 4)
			print_buf();
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
		return (4);
	}
	return (0);
}

void		print_c(const wchar_t c, t_frmt *prm)
{
	char	*width;

	if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		prm->flags ^= F_ZERO;
	if (c <= 0x7FF)
		prm->len = (c <= 0x7F ? 1 : 2);
	else
		prm->len = (c <= 0xFFFF ? 3 : 4);
	width = make_width(prm);
	if (width && !(prm->flags & F_MINUS))
		string_to_buf(width);
	if (prm->mod == L || prm->spec == 'C')
		unicode(c);
	else
	{
		*(g_buf + g_len) = c;
		++g_len;
		if (g_len == BUFF_SIZE)
			print_buf();
	}
	if (width && prm->flags & F_MINUS)
		string_to_buf(width);
	if (width)
		free(width);
}

void		print_s(char *s, t_frmt *prm)
{
	char	*width;

	if (!s)
		s = (prm->precision - (prm->flags & F_PREC) ? "(null)" : "");
	if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		prm->flags ^= F_ZERO;
	prm->len = ft_strlen(s);
	if (prm->flags & F_PREC)
		prm->len = MIN(prm->precision - (prm->flags & F_PREC), prm->len);
	width = make_width(prm);
	if (width && !(prm->flags & F_MINUS))
		string_to_buf(width);
	while (prm->len > 0)
	{
			*(g_buf + g_len) = *s;
			++g_len;
			if (g_len == BUFF_SIZE)
				print_buf();
			--prm->len;
			++s;
	}
	if (width && prm->flags & F_MINUS)
		string_to_buf(width);
	if (width)
		free(width);
}

static int	strsize(const wchar_t *s, t_frmt *prm)
{
	int i;
	int size;

	i = 0;
	size = 0;
	prm->precision -= prm->flags & F_PREC;
	while (*s && (prm->flags & F_PREC ? prm->precision > 0 : 1))
	{
		if (*s <= 0x7FF)
		{
			i = (*s <= 0x7F ? 1 : 2);
			size += i;
			if (prm->flags & F_PREC)
				prm->precision -= i;
		}
		else
		{
			i = (*s <= 0xFFFF ? 3 : 4);
			size += i;
			if (prm->flags & F_PREC)
				prm->precision -= i;
		}
		++s;
	}
	return ((prm->flags & F_PREC) && prm->precision < 0 ? size - i : size);
}

void		print_ws(wchar_t *s, t_frmt *prm)
{
	char	*width;

	if (!s)
		print_s(NULL, prm);
	else
	{
		if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
			prm->flags ^= F_ZERO;
		prm->len = strsize(s, prm);
		width = make_width(prm);
		if (width && !(prm->flags & F_MINUS))
			string_to_buf(width);
		while (prm->len > 0)
		{
			prm->len -= unicode(*s);
			++s;
		}
		if (width && prm->flags & F_MINUS)
			string_to_buf(width);
		if (width)
			free(width);
	}
}