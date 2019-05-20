/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 13:27:56 by smorty            #+#    #+#             */
/*   Updated: 2019/05/20 21:18:49 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_x(uintmax_t n)
{
	uintmax_t	d;
	int			size;

	size = 1;
	n /= 16;
	d = 1;
	while (d <= n)
	{
		d *= 16;
		size++;
	}
	return (size);
}

static void	xtoa(char *s, uintmax_t n, int spec)
{
	spec = (spec == 'x' || spec == 'p' ? 87 : 55);
	while (n)
	{
		*s = n % 16;
		*s += (*s > 9 ? spec : '0');
		n /= 16;
		s--;
	}
}

static void	prefix_x(char *s, int n_is_zero, t_frmt *prm)
{
	if (prm->spec == 'p')
	{
		*s = '0';
		*(s + 1) = 'x';
	}
	else if (!n_is_zero && prm->flags & F_HASH)
	{
		*s = '0';
		*(s + 1) = prm->spec;
	}
}

static void	process_x_mod(uintmax_t n, t_frmt *prm)
{
	char	*out;
	char	*width;
	int		prec;

	if (prm->flags & F_ZERO && prm->flags & (F_MINUS | F_PREC))
		prm->flags ^= F_ZERO;
	prec = prm->precision - (prm->flags & F_PREC);
	prm->len = MAX(num_len_x(n), prec);
	if ((n && prm->flags & F_HASH) || prm->spec == 'p')
		prm->len += 2;
	if (!(out = (char *)malloc(sizeof(char) * (prm->len + 1))))
	{
		g_error = -1;
		return ;
	}
	ft_memset(out, '0', prm->len);
	if (!n && !prec)
		prm->len = (prm->spec == 'p' ? 2 : 0);
	else
		xtoa(out + prm->len - 1, n, prm->spec);
	width = make_width(prm);
	prefix_x((width && (prm->flags & F_ZERO) ? width : out), !n, prm);
	to_print(out, width, prm);
}

void		process_x(va_list *argp, t_frmt *params)
{
	if ((*params).spec == 'p')
	{
		(*params).flags |= F_HASH;
		process_x_mod(va_arg(*argp, intptr_t), params);
	}
	else if ((*params).mod == HH)
		process_x_mod((unsigned char)va_arg(*argp, unsigned int), params);
	else if ((*params).mod == H)
		process_x_mod((unsigned short)va_arg(*argp, unsigned int), params);
	else if ((*params).mod == NO)
		process_x_mod(va_arg(*argp, unsigned int), params);
	else if ((*params).mod == L)
		process_x_mod(va_arg(*argp, unsigned long), params);
	else if ((*params).mod == LL)
		process_x_mod(va_arg(*argp, unsigned long long), params);
	else if ((*params).mod == Z)
		process_x_mod(va_arg(*argp, size_t), params);
	else if ((*params).mod == J)
		process_x_mod(va_arg(*argp, uintmax_t), params);
}
