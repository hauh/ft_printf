/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_feg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 18:18:09 by smorty            #+#    #+#             */
/*   Updated: 2019/05/28 15:56:26 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_exponent(char *out)
{
	int e;

	e = -1;
	if (*out == '.')
	{
		++out;
		while (*out == '0')
		{
			++out;
			--e;
		}
		if (!*out)
			e = 0;
	}
	else
		while (*out != '.')
		{
			++out;
			++e;
		}
	return (e);
}

static void comb(char *power, char *p_end)
{
	while (p_end >= power)
	{
		while (*p_end > 9)
		{
			*p_end -= 10;
			++(*(p_end - 1));
		}
		--p_end;
	}
}

void pwr2(char *dot, int pwr)
{
	char power[pwr / 2 + 2];
	char *p;
	char *p_end;

	ft_bzero(power, pwr / 2 + 2);
	p_end = power + pwr / 2 + 1;
	*(power + pwr / 2) = 1;
	while (pwr)
	{
		p = power;
		while (p < p_end)
			*p++ *= 2;
		comb(power, p_end);
		--pwr;
	}
	p = dot - 1;
	while (p_end >= power)
	{
		--p_end;
		*p += *p_end;
		--p;
	}
	comb(p, dot - 1);
}

void pwr2neg(char *dot, int pwr)
{
	char power[pwr + 1];
	char *p;
	char *p_end;

	ft_bzero(power, pwr + 1);
	p_end = power + pwr;
	*(power + pwr - 1) = 1;
	while (pwr)
	{
		p = power;
		while (p < p_end)
			*p++ *= 5;
		comb(power, p_end);
		--pwr;
	}
	p = power;
	while (p < p_end)
	{
		*dot += *p;
		++dot;
		++p;
	}
	comb(dot - (p_end - &power[0]), dot);
}

void round_float(char *out, char *dot, char *end)
{
	int dif;
	char *p;

	dif = 0;
	if (*(end + 1) == '5' && !(*end % 2))
	{
		p = end + 2;
		while (*p == '0')
			++p;
		if (*p)
			dif = 1;
	}
	if (*(end + 1) > '5' || dif)
	{
		dif = 1;
		while (dif && end > dot)
		{
			++(*end);
			*end > '9' ? (*end = '0') : (dif = 0);
			--end;
		}
		--end;
		while (dif && end >= out)
		{
			++(*end);
			*end > '9' ? (*end = '0') : (dif = 0);
			--end;
		}
	}
}

int prefix_feg(char *out, int sign, int flags)
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

void shift_dot(char *out, int precision)
{
	if (*out == '.')
	{
		*out++ = '0';
		while (*out == '0')
			++out;
		if (*out)
		{
			*(out - 1) = *out;
			*out = '.';
		}
		else
			*(out - precision) = '.';
	}
	else
	{
		*(out - 1) = *out;
		*out++ = '.';
		while (*out != '.')
			++out;
		while (*out)
		{
			*out = *(out + 1);
			++out;
		}
	} 
}

void trim_zeros(char *out)
{
	while (*out == '0')
		*out-- = 0;
	if (*out == '.')
		*out = 0;
}

void *ftoa(t_ld *nb, t_frmt *prm)
{
	char	*dot;
	char	*out;
	char	*out_end;
	int		size;
	int		exponent;

	exponent = nb->exponent;
	size = MAX(65, ABS(exponent)) + prm->precision + 7;
	out = (char *)malloc(sizeof(char) * size * 2);
	out_end = out + size;
	ft_bzero(out, size);
	dot = out + (exponent > 0 ? exponent : 2);
	*dot = '.';
	size = 63;
	while (size >= 0)
	{
		if (nb->mantissa & (1L << size))
			exponent >= 0 ? pwr2(dot, exponent) : pwr2neg(dot + 1, -exponent);
		--exponent;
		--size;
	}
	while (out_end >= out)
		*out_end-- += '0';
	*dot = '.';
	return(out);
}

void process_feg(t_ld *nb, t_frmt *prm)
{
	char	*out0;
	char	*out;
	char	*dot;
	int		spec;
	int		e;

	spec = prm->spec;

	out0 = ftoa(nb, prm);
	out = out0;
	while (*out == '0')
		++out;
	e = get_exponent(out);
	if (spec == 'g' || spec == 'G')
	{
		if (e < prm->precision && e >= -4)
			prm->precision -= e;
		else
			--spec;
		if (prm->precision)
			--prm->precision;
		--spec;
	}
	if (spec == 'e' || spec == 'E')
		shift_dot(out, prm->precision);
	dot = out;
	while (*dot != '.')
		++dot;
	round_float(out0, dot, dot + prm->precision);
	if (!prm->precision)
		*dot = 0;
	else
		*(dot + 1 + prm->precision) = 0;
	if ((prm->spec == 'g' || prm->spec == 'G') && !(prm->flags & F_HASH))
		trim_zeros(dot + prm->precision);
	while (*dot)
		++dot;
	if (spec == 'e' || spec == 'E')
		suffix_float(dot, e, spec);
	out = out0;
	while (*out == '0')
		++out;
	if (*out == '.' || !*out)
		--out;
	out -= prefix_feg(out - 1, nb->sign, prm->flags);
	prm->len = ft_strlen(out);
	to_print(out, make_width(prm), prm);
	free(out0);
}
