/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:57:07 by smorty            #+#    #+#             */
/*   Updated: 2019/05/24 22:03:22 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_u(uintmax_t n)
{
	uintmax_t	d;
	int			size;

	size = 1;
	n /= 10;
	d = 1;
	while (d <= n)
	{
		d *= 10;
		size++;
	}
	return (size);
}

static void	utoa(char *s, uintmax_t n)
{
	while (n)
	{
		s--;
		*s = n % 10 + '0';
		n /= 10;
	}
}

static void	process_u_mod(uintmax_t n, t_frmt *prm)
{
	char	*out;
	int		precision;

	if (prm->flags & F_ZERO && prm->flags & (F_MINUS | F_PREC))
		prm->flags ^= F_ZERO;
	precision = prm->precision - (prm->flags & F_PREC);
	prm->len = num_len_u(n);
	prm->len = MAX(prm->len, precision);
	if (!(out = (char *)malloc(sizeof(char) * (prm->len + 1))))
	{
		g_error = -1;
		return ;
	}
	ft_memset(out, '0', prm->len);
	if (!n && !precision)
		prm->len = 0;
	else
		utoa(out + prm->len, n);
	*(out + prm->len) = 0;
	to_print(out, make_width(prm), prm);
	free(out);
}

void		process_u(va_list *argp, t_frmt *params)
{
	if ((*params).mod == HH)
		process_u_mod((unsigned char)va_arg(*argp, unsigned int), params);
	else if ((*params).mod == H)
		process_u_mod((unsigned short)va_arg(*argp, unsigned int), params);
	else if ((*params).mod == NO)
		process_u_mod(va_arg(*argp, unsigned int), params);
	else if ((*params).mod == L)
		process_u_mod(va_arg(*argp, unsigned long), params);
	else if ((*params).mod == LL)
		process_u_mod(va_arg(*argp, unsigned long long), params);
	else if ((*params).mod == Z)
		process_u_mod(va_arg(*argp, size_t), params);
	else if ((*params).mod == J)
		process_u_mod(va_arg(*argp, uintmax_t), params);
}
