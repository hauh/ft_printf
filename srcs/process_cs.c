/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:49:39 by smorty            #+#    #+#             */
/*   Updated: 2019/05/28 22:33:56 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		process_c(const wchar_t c, t_frmt *prm)
{
	if (c <= 0x7FF)
		prm->len = (c <= 0x7F ? 1 : 2);
	else
		prm->len = (c <= 0xFFFF ? 3 : 4);
	if (!(prm->flags & F_MINUS) && prm->width > prm->len)
		char_to_buf((prm->flags & F_ZERO ? '0' : ' '), prm->width - prm->len);
	if (prm->mod == L || prm->spec == 'C')
		unicode(c);
	else
		char_to_buf(c, 1);
	if ((prm->flags & F_MINUS) && prm->width > prm->len)
		char_to_buf((prm->flags & F_ZERO ? '0' : ' '), prm->width - prm->len);
}

void		process_s(const char *s, t_frmt *prm)
{
	int width;

	if (!s)
		s = (!prm->precision && prm->flags & F_PREC ? "" : "(null)");
	prm->len = ft_strlen(s);
	if (prm->flags & F_PREC)
		prm->len = MIN(prm->precision, prm->len);
	width = prm->width - prm->len;
	if (!(prm->flags & F_MINUS) && width > 0)
		char_to_buf((prm->flags & F_ZERO ? '0' : ' '), width);
	while (prm->len > 0)
	{
		char_to_buf(*s, 1);
		--prm->len;
		++s;
	}
	if ((prm->flags & F_MINUS) && width > 0)
		char_to_buf((prm->flags & F_ZERO ? '0' : ' '), width);
}

static int	strsize(const wchar_t *s, t_frmt *prm)
{
	int size;
	int i;

	i = 0;
	size = 0;
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

static void	process_ls(const wchar_t *s, t_frmt *prm)
{
	int width;

	if (!s)
		process_s(NULL, prm);
	else
	{
		prm->len = strsize(s, prm);
		width = prm->width - prm->len;
		if (!(prm->flags & F_MINUS) && width > 0)
			char_to_buf((prm->flags & F_ZERO ? '0' : ' '), width);
		while (prm->len > 0)
		{
			prm->len -= unicode(*s);
			++s;
		}
		if ((prm->flags & F_MINUS) && width > 0)
			char_to_buf((prm->flags & F_ZERO ? '0' : ' '), width);
	}
}

void		process_cs(va_list *argp, t_frmt *prm)
{
	if ((prm->flags & (F_ZERO | F_MINUS)) == (F_ZERO | F_MINUS))
		prm->flags ^= F_ZERO;
	--prm->precision;
	if (prm->spec == 'c' || prm->spec == 'C')
	{
		if (prm->mod == L || prm->spec == 'C')
			process_c((const wchar_t)va_arg(*argp, int), prm);
		else
			process_c((const char)va_arg(*argp, int), prm);
	}
	else
	{
		if (prm->mod == L || prm->spec == 'S')
			process_ls(va_arg(*argp, const wchar_t *), prm);
		else
			process_s(va_arg(*argp, const char *), prm);
	}
}
