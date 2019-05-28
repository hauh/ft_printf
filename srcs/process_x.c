/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 13:27:56 by smorty            #+#    #+#             */
/*   Updated: 2019/05/28 23:50:48 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	xtoa(char **s, uintmax_t n, int *precision, int spec)
{
	spec = (spec > 'a' ? 87 : 55);
	while (n)
	{
		**s = n % 16;
		**s += (**s > 9 ? spec : '0');
		n /= 16;
		--(*s);
		--(*precision);
	}
}

static int	prefix_x(char *s, int n_is_zero, t_frmt *prm)
{
	if (prm->spec == 'p')
	{
		*s-- = 'x';
		*s = '0';
	}
	else if (!n_is_zero && prm->flags & F_HASH)
	{
		*s-- = prm->spec;
		*s = '0';
	}
	else
		return (-1);
	return (1);
}

static void	process_x_mod(uintmax_t n, t_frmt *prm)
{
	char	*out;
	char	*out0;
	int		size;
	int		precision;

	precision = prm->precision - (prm->flags & F_PREC);
	size = MAX(precision, 20) + 3;
	out = (char *)malloc(sizeof(char) * (size + 1));
	out0 = out;
	out += size;
	*out-- = 0;
	if (n)
		xtoa(&out, n, &precision, prm->spec);
	while (precision-- > 0)
		*out-- = '0';
	out -= prefix_x(out, (!n), prm);
	prm->len = ft_strlen(out);
	to_print(out, make_width(prm), prm);
	free(out0);
}

void		process_x(va_list *argp, t_frmt *prm)
{
	if (prm->flags & F_ZERO)
	{
		if (prm->flags & (F_MINUS | F_PREC))
			prm->flags ^= F_ZERO;
		else if (prm->width > prm->precision)
		{
			prm->flags |= F_PREC;
			prm->precision = prm->width - 1;
		}
	}
	if (prm->spec == 'p')
	{
		prm->flags |= F_HASH;
		process_x_mod(va_arg(*argp, intptr_t), prm);
	}
	else if (prm->mod == HH)
		process_x_mod((unsigned char)va_arg(*argp, unsigned int), prm);
	else if (prm->mod == H)
		process_x_mod((unsigned short)va_arg(*argp, unsigned int), prm);
	else if (prm->mod == NO)
		process_x_mod(va_arg(*argp, unsigned int), prm);
	else if (prm->mod == L)
		process_x_mod(va_arg(*argp, unsigned long), prm);
	else if (prm->mod == LL)
		process_x_mod(va_arg(*argp, unsigned long long), prm);
	else if (prm->mod == Z)
		process_x_mod(va_arg(*argp, size_t), prm);
	else if (prm->mod == J)
		process_x_mod(va_arg(*argp, uintmax_t), prm);
}
