/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:58:45 by smorty            #+#    #+#             */
/*   Updated: 2019/05/24 22:03:35 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_o(uintmax_t n)
{
	uintmax_t	d;
	int			size;

	size = 1;
	n /= 8;
	d = 1;
	while (d <= n)
	{
		d *= 8;
		size++;
	}
	return (size);
}

static void	otoa(char *s, uintmax_t n)
{
	while (n)
	{
		*s = n % 8 + '0';
		n /= 8;
		s--;
	}
}

static void	process_o_mod(uintmax_t n, t_frmt *prm)
{
	char	*out;
	int		precision;

	if (prm->flags & F_ZERO && prm->flags & (F_MINUS | F_PREC))
		prm->flags ^= F_ZERO;
	precision = prm->precision - (prm->flags & F_PREC);
	prm->len = num_len_o(n) + (n && (prm->flags & F_HASH) ? 1 : 0);
	prm->len = MAX(prm->len, precision);
	if (!(out = (char *)malloc(sizeof(char) * (prm->len + 1))))
	{
		g_error = -1;
		return ;
	}
	ft_memset(out, '0', prm->len);
	if (!n && !precision)
		prm->len = (prm->flags & F_HASH ? 1 : 0);
	else
		otoa(out + prm->len - 1, n);
	*(out + prm->len) = 0;
	to_print(out, make_width(prm), prm);
	free(out);
}

void		process_o(va_list *argp, t_frmt *params)
{
	if ((*params).mod == HH)
		process_o_mod((unsigned char)va_arg(*argp, unsigned int), params);
	else if ((*params).mod == H)
		process_o_mod((unsigned short)va_arg(*argp, unsigned int), params);
	else if ((*params).mod == NO)
		process_o_mod(va_arg(*argp, unsigned int), params);
	else if ((*params).mod == L)
		process_o_mod(va_arg(*argp, unsigned long), params);
	else if ((*params).mod == LL)
		process_o_mod(va_arg(*argp, unsigned long long), params);
	else if ((*params).mod == Z)
		process_o_mod(va_arg(*argp, size_t), params);
	else if ((*params).mod == J)
		process_o_mod(va_arg(*argp, uintmax_t), params);
}
