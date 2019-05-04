/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:42:26 by smorty            #+#    #+#             */
/*   Updated: 2019/05/04 17:52:09 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_minusf(char *s, t_frmt params)
{
	int		printed;
	char	*s0;

	s0 = s;
	printed = 0;
	if (*s < 0)
	{
		printed += write(1, "-", 1);
		s++;
	}
	else if (params.plus)
		printed += write(1, "+", 1);
	else if (params.space)
		printed += write(1, " ", 1);
	while (params.precision > 0)
	{
		printed += write(1, "0", 1);
		params.precision--;
	}
	while (*s)
	{
		printed += write(1, s, 1);
		s++;
	}
	while (params.width > 0)
	{
		printed += write(1, " ", 1);
		params.width--;
	}
	free(s0);
	return (printed);
}

static int	print_zerof(char *s, t_frmt params)
{
	int		printed;
	char	*s0;

	s0 = s;
	printed = 0;
	if (*s < 0)
	{
		printed += write(1, "-", 1);
		s++;
	}
	else if (params.plus)
		printed += write(1, "+", 1);
	else if (params.space)
		printed += write(1, " ", 1);
	while (params.width > 0)
	{
		printed += write(1, "0", 1);
		params.width--;
	}
	while (*s)
	{
		printed += write(1, s, 1);
		s++;
	}
	free(s0);
	return (printed);
}

static int	print_nof(char *s, t_frmt params)
{
	int		printed;
	char	*s0;

	s0 = s;
	printed = 0;
	while (params.width > 0)
	{
		printed += write(1, " ", 1);
		params.width--;
	}
	if (*s < 0)
	{
		printed += write(1, "-", 1);
		s++;
	}
	else if (params.plus)
		printed += write(1, "+", 1);
	else if (params.space)
		printed += write(1, " ", 1);
	while (params.precision > 0)
	{
		printed += write(1, "0", 1);
		params.precision--;
	}
	while (*s)
	{
		printed += write(1, s, 1);
		s++;
	}
	free(s0);
	return (printed);
}

int	print_number_base(long long n, t_frmt params, int base)
{
	char *s;

	if (params.precision >= 0)
		params.zero = 0;
	s = ntoa_base(n, base, &params);
	if (!s)
		return (-1);
	if (params.precision > 0)
		params.width -= params.precision;
	if (params.plus || params.space || n < 0)
		params.width--;
	if (params.minus)
		return (print_minusf(s, params));
	else if (params.zero)
		return (print_zerof(s, params));
	else
		return (print_nof(s, params));
}

int	print_number_base_u(unsigned long long n, t_frmt params, int base)
{
	char *s;

	if (params.precision >= 0)
		params.zero = 0;
	s = ntoa_base_u(n, base, &params);
	if (!s)
		return (-1);
	if (params.precision > 0)
		params.width -= params.precision;
	if (params.plus || params.space)
		params.width--;
	if (params.minus)
		return (print_minusf(s, params));
	else if (params.zero)
		return (print_zerof(s, params));
	else
		return (print_nof(s, params));
}