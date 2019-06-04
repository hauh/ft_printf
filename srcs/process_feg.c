/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_feg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 18:18:09 by smorty            #+#    #+#             */
/*   Updated: 2019/06/04 23:13:30 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_exponent(char *out)
{
	int e;

	e = 0;
	while (*out == '0')
		++out;
	if (*out++ == '.')
	{
		--e;
		while (*out++ == '0')
			--e;
		if (!*out)
			return (0);
	}
	else
		while (*out++ != '.')
			++e;
	return (e);
}

static void	round_float(char *dot, char *end)
{
	char	*p;
	int		dif;

	if (*end >= '5')
	{
		dif = 1;
		if (*end == '5' && !(*(end - (*(end - 1) == '.' ? 2 : 1)) % 2))
		{
			p = end + 1;
			while (*p == '0')
				++p;
			if (!*p)
				dif = 0;
		}
		while (dif && --end > dot)
			if (++(*end) > '9')
				*end = '0';
			else
				dif = 0;
		while (dif && --end)
			if (++(*end) > '9')
				*end = '0';
			else
				dif = 0;
	}
}

static int	prefix_feg(char *out, int sign, int flags)
{
	if (sign)
	{
		*out = '-';
		return (1);
	}
	else if (flags & F_PLUS)
	{
		*out = '+';
		return (1);
	}
	else if (flags & F_SPACE)
	{
		*out = ' ';
		return (1);
	}
	return (0);
}

static char	*shift_dot(char *dot, int exponent)
{
	while (exponent > 0)
	{
		*dot = *(dot - 1);
		--dot;
		--exponent;
	}
	while (exponent < 0)
	{
		*dot = *(dot + 1);
		++dot;
		++exponent;
	}
	*dot = '.';
	return (dot);
}

static int	trim_zeros(char *out)
{
	int cut;

	cut = 0;
	while (*out == '0')
	{
		*out-- = 0;
		++cut;
	}
	if (*out == '.')
	{
		*out = 0;
		++cut;
	}
	return (cut);
}

static int	process_feg_2(char *out, t_frmt *prm, int sign)
{
	char *dot;
	char *width;

	dot = out;
	while (*dot == '0')
		++dot;
	if (*dot < '0' || *dot > '9')
		--dot;
	prm->len = ft_strlen(dot);
	width = NULL;
	if (prm->width > prm->len)
		if (!(width = make_width(prm)))
			return (g_ftprintf.error = -1);
	if (width && prm->flags & F_ZERO)
		prefix_feg(width, sign, prm->flags);
	else if (prefix_feg(dot - 1, sign, prm->flags))
	{
		--dot;
		++prm->len;
		--prm->width;
	}
	to_print(dot, width, prm);
	free(out);
	return (0);
}

int			process_feg(char *out, t_frmt *prm, int sign)
{
	char	*dot;
	int		spec;
	int		e;

	spec = prm->spec;
	dot = out;
	while (*dot != '.')
		++dot;
	e = get_exponent(out);
	if (spec == 'g' || spec == 'G')
	{
		if (e < prm->precision && e >= -4)
			prm->precision -= e;
		else
			--spec;
		--spec;
	}
	if (spec == 'e' || spec == 'E')
		dot = shift_dot(dot, e);
	round_float(dot, dot + prm->precision + 1);
	if ((prm->spec == 'g' || prm->spec == 'G') && !(prm->flags & F_HASH))
		prm->precision -= trim_zeros(dot + prm->precision);
	if (spec == 'e' || spec == 'E')
		suffix_float(dot + (prm->precision ? prm->precision + 1 : prm->flags & F_HASH), e, spec);
	else
		*(dot + (prm->precision || prm->flags & F_HASH ? prm->precision + 1 : 0)) = 0;
	return (process_feg_2(out, prm, sign));
}
