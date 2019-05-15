/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:58:45 by smorty            #+#    #+#             */
/*   Updated: 2019/05/15 21:30:30 by smorty           ###   ########.fr       */
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
	if (!n)
		*s = '0';
	while (n)
	{
		*s = n % 8 + '0';
		n /= 8;
		s--;
	}
}

void		print_o(uintmax_t n, t_frmt *prm)
{
	char	*out;
	char	*width;
	int		prec;

	if (prm->flags & F_ZERO && prm->flags & (F_MINUS | F_PREC))
		prm->flags ^= F_ZERO;
	prec = prm->precision - (prm->flags & F_PREC);
	prm->len = MAX(num_len_o(n), prec) + (n && (prm->flags & F_HASH) ? 1 : 0);
	if (!(out = (char *)malloc(sizeof(char) * prm->len)))
		error();
	ft_memset(out, '0', prm->len);
	if (!n && !prec)
		prm->len = (prm->flags & F_HASH ? 1 : 0);
	else
		otoa(out + prm->len - 1, n);
	width = NULL;
	if (prm->width > prm->len)
		if (!(width = get_width(prm)))
			error();
	print(out, width, prm);
}
