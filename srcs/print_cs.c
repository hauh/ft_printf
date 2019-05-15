/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:49:39 by smorty            #+#    #+#             */
/*   Updated: 2019/05/15 21:39:40 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


static int	unicode(char *g_buf, wchar_t c)
{
	if (c <= 0x7F)
	{
		*g_buf = (c & 0x7F);
		++g_len;
		if (g_len == BUFF_SIZE)
			print_buf();
		return (1);
	}
	else if (c <= 0x7FF && BUFF_SIZE >= 2)
	{
		if (BUFF_SIZE - g_len < 2)
			print_buf();
		*(g_buf + 1) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*g_buf = 0xC0 | (c & 0x1F);
		g_len += 2;
		if (g_len == BUFF_SIZE)
			print_buf();
		return (2);
	}
	else if (c <= 0xFFFF && BUFF_SIZE >= 3)
	{
		if (BUFF_SIZE - g_len < 3)
			print_buf();
		*(g_buf + 2) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*(g_buf + 1) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*g_buf = 0xE0 | (c & 0xF);
		g_len += 3;
		if (g_len == BUFF_SIZE)
			print_buf();
		return (3);
	}
	else if (c <= 0x10FFFF && BUFF_SIZE >= 4)
	{
		if (BUFF_SIZE - g_len < 4)
			print_buf();
		*(g_buf + 3) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*(g_buf + 2) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*(g_buf + 1) = 0x80 | (c & 0x3F);
		c = (c >> 6);
		*g_buf = 0xF0 | (c & 0x7);
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
	width = NULL;
	if (--prm->width > 0)
		if (!(width = get_width(prm)))
			error();
	if (width && !(prm->flags & F_MINUS))
		move_to_buf(width);
	unicode(g_buf + g_len, c);
	if (width && prm->flags & F_MINUS)
		move_to_buf(width);
	if (width)
		free(width);
}

void		print_s(char *s, t_frmt *prm)
{
	char	*width;
	int		printed;

	if (!s)
		s = (prm->precision - (prm->flags & F_PREC) ? "(null)" : "");
	if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		prm->flags ^= F_ZERO;
	prm->len = ft_strlen(s);
	if (prm->flags & F_PREC)
		prm->len = MIN(prm->precision - (prm->flags & F_PREC), prm->len);
	width = NULL;
	if (prm->width > prm->len)
		if (!(width = get_width(prm)))
			error();
	if (width && !(prm->flags & F_MINUS))
		move_to_buf(width);
	move_to_buf(s);
	if (width && prm->flags & F_MINUS)
		move_to_buf(width);
	if (width)
		free(width);
}

int			lensize(const wchar_t *s)
{
	int size;

	size = 0;
	while (*s)
	{
		if (*s <= 0x7F)
			++size;
		else if (*s <= 0x7FF)
			size += 2;
		else if (*s <= 0xFFFF)
			size += 3;
		else
			size += 4;
		++s;
	}
	return (size);
}

void		print_ws(wchar_t *s, t_frmt *prm)
{
	char	*width;
	int		printed;

	if (!s)
		print_s(NULL, prm);
	else
	{
		if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
			prm->flags ^= F_ZERO;
		prm->len = lensize(s);
		if (prm->flags & F_PREC)
			prm->len = MIN(prm->precision - (prm->flags & F_PREC), prm->len);
		width = NULL;
		if (prm->width > prm->len)
			if (!(width = get_width(prm)))
				error();
		if (width && !(prm->flags & F_MINUS))
			move_to_buf(width);
		while (prm->len > 0)
		{
			prm->len -= unicode(g_buf + g_len, *s);
			++s;
		}
		if (width && prm->flags & F_MINUS)
			move_to_buf(width);
		if (width)
			free(width);
	}
}