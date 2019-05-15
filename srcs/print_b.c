/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 20:24:09 by smorty            #+#    #+#             */
/*   Updated: 2019/05/15 17:20:49 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len_b(uintmax_t n)
{
	uintmax_t	d;
	int			size;

	size = 1;
	n /= 2;
	d = 1;
	while (d <= n)
	{
		d *= 2;
		size++;
	}
	return (size);
}

static void	btoa(char *s, uintmax_t n)
{
	if (!n)
		*s = '0';
	while (n)
	{
		*s = n % 2 + '0';
		n /= 2;
		s--;
	}
}

static void	prefix_b(char *s, uintmax_t n, t_frmt *prm)
{
	if (n && prm->flags & F_HASH)
	{
		*s = '0';
		*(s + 1) = prm->spec;
	}
}

void		print_b(uintmax_t n, t_frmt *prm)
{
	char	*out;
	char	*width;
	int		prec;

	if (prm->flags & F_ZERO && prm->flags & (F_MINUS | F_PREC))
		prm->flags ^= F_ZERO;
	prec = prm->precision - (prm->flags & F_PREC);
	prm->len = MAX(num_len_b(n), prec) + (n && (prm->flags & F_HASH) ? 2 : 0);
	if (!(out = (char *)malloc(sizeof(char) * prm->len)))
		error();
	ft_memset(out, '0', prm->len);
	if (!n && !prec)
		prm->len = 0;
	else
		btoa(out + prm->len - 1, n);
	width = NULL;
	if (prm->width > prm->len)
		if (!(width = get_width(prm)))
			error();
	prefix_b((width && (prm->flags & F_ZERO) ? width : out), n, prm);
	print(out, width, prm);
}
