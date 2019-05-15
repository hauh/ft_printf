/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 13:27:56 by smorty            #+#    #+#             */
/*   Updated: 2019/05/15 17:07:43 by smorty           ###   ########.fr       */
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
	if (!n)
		*s = '0';
	spec = (spec == 'x' || spec == 'p' ? 87 : 55);
	while (n)
	{
		*s = n % 16;
		*s += (*s > 9 ? spec : '0');
		n /= 16;
		s--;
	}
}

static void	prefix_x(char *s, uintmax_t n, t_frmt *prm)
{
	if (prm->spec == 'p')
	{
		*s = '0';
		*(s + 1) = 'x';
	}
	else if (n && prm->flags & F_HASH)
	{
		*s = '0';
		*(s + 1) = prm->spec;
	}
}

void		print_x(uintmax_t n, t_frmt *prm)
{
	char	*out;
	char	*width;
	int		prec;

	if (prm->flags & F_ZERO && prm->flags & (F_MINUS | F_PREC))
		prm->flags ^= F_ZERO;
	prec = prm->precision - (prm->flags & F_PREC);
	prm->len = MAX(num_len_x(n), prec);
	prm->len += (((n && (prm->flags & F_HASH)) || prm->spec == 'p') ? 2 : 0);
	if (!(out = (char *)malloc(sizeof(char) * (prm->len + 1))))
		error();
	ft_memset(out, '0', prm->len);
	if (!n && !prec)
		prm->len = (prm->spec == 'p' ? 2 : 0);
	else
		xtoa(out + prm->len - 1, n, prm->spec);
	width = NULL;
	if (prm->width > prm->len)
		if (!(width = get_width(prm)))
			error();
	prefix_x((width && (prm->flags & F_ZERO) ? width : out), n, prm);
	print(out, width, prm);
}
