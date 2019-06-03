/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_feg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 18:18:09 by smorty            #+#    #+#             */
/*   Updated: 2019/06/03 23:25:02 by smorty           ###   ########.fr       */
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

static int *multiply(int *a, int *b, int size_a, int size_b)
{
	int *result;
	int size;
	int i;
	int j;

	size = size_a + size_b + 1;
	result = (int *)malloc(sizeof(int) * (size + 1));
	ft_bzero(result, sizeof(int) * (size + 1));
	i = 0;
	while (i < size_a)
	{
		j = 0;
		while (j < size_b)
		{
			result[1 + i + j] += a[i] * b[j];
			++j;
		}
		++i;
	}
	while (--size)
		if (result[size] > 9)
		{
			result[size - 1] += result[size] / 10;
			result[size] %= 10;
		}
	free(a);
	return (result);
}

static int new_size(int **result, int len)
{
	int *new;
	int i;
	int j;

	i = 0;
	while (!(*result)[i])
		++i;
	new = (int *)malloc(sizeof(int) * (len - i));
	j = 0;
	while (i < len)
	{
		*(new + j) = (*result)[i];
		++j;
		++i;
	}
	free(*result);
	*result = new;
	return (j);
}

static int *power2pos(int power, int *len_r)
{
	int *result;
	int *pwr;
	int len_p;

	result = (int *)malloc(sizeof(int));
	*result = 1;
	*len_r = 1;
	pwr = (int *)malloc(sizeof(int));
	*pwr = 2;
	len_p = 1;
	while (power)
	{
		if (power & 1)
		{
			result = multiply(result, pwr, *len_r, len_p);
			*len_r = new_size(&result, *len_r + len_p);
		}
		pwr = multiply(pwr, pwr, len_p, len_p);
		len_p = new_size(&pwr, len_p * 2);
		power >>= 1;
	}
	free(pwr);
	return (result);
}

static int	*power2neg(int power, int *len_r)
{
	int *result;
	int *pwr;
	int len_p;

	result = (int *)malloc(sizeof(int));
	*result = 1;
	*len_r = 1;
	pwr = (int *)malloc(sizeof(int));
	*pwr = 5;
	len_p = 1;
	while (power)
	{
		if (power & 1)
		{
			result = multiply(result, pwr, *len_r, len_p);
			*len_r += len_p;
		}
		pwr = multiply(pwr, pwr, len_p, len_p);
		len_p *= 2;
		power >>= 1;
	}
	free(pwr);
	return (result);
}

static void power2(char *dot, int power)
{
	int *result;
	int len;

	result = power < 0 ? power2neg(-power, &len) : power2pos(power, &len);
	dot += (power < 0 ? len - 1 : -1);
	result += len - 1;
	while (len--)
	{
		*dot += *result;
		if (*dot > 9 && *dot != '.')
		{
			*dot -= 10;
			++*(dot - 1);
		}
		--dot;
		--result;
	}
	while (*dot > 9)
	{
		*dot -= 10;
		--dot;
		++*dot;
	}
	free(result + 1);
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

	size = MAX(65, ABS(nb->exponent)) + prm->precision + 7;
	out = (char *)malloc(sizeof(int) * size * 2);
	out_end = out + size;
	ft_bzero(out, size);
	dot = out + (nb->exponent > 0 ? nb->exponent : 2);
	*dot = '.';
	size = 0;
	exponent = nb->exponent - 63;
	while (size < 64)
	{
		if (nb->mantissa & (1L << size))
			power2(dot, exponent);
		++exponent;
		++size;
	}
	while (out_end >= out)
		*out_end-- += '0';
	*dot = '.';
	return (out);
}

int process_feg(t_ld *nb, t_frmt *prm)
{
	char	*out0;
	char	*out;
	char	*dot;
	char	*width;
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
	width = NULL;
	if (prm->width > prm->len)
		if (!(width = make_width(prm)))
			return (g_ftprintf.error = -1);
	to_print(out, width, prm);
	free(out0);
	return (0);
}
