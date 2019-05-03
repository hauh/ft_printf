/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:46:54 by smorty            #+#    #+#             */
/*   Updated: 2019/05/03 23:08:38 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_minusf(unsigned long long n, unsigned long long l, t_frmt prm)
{
	int printed;

	printed = 0;
	if (prm.plus)
		printed += write(1, "+", 1);
	else if (prm.space)
		printed += write(1, " ", 1);
	while (prm.precision > 0)
	{
		printed += write(1, "0", 1);
		prm.precision--;
	}
	while (l)
	{
		ft_putchar(n / l + '0');
		n %= l;
		l /= 10;
		printed++;
	}
	while (prm.width > 0)
	{
		printed += write(1, " ", 1);
		prm.width--;
	}
	return (printed);
}

static int	print_zerof(unsigned long long n, unsigned long long l, t_frmt prm)
{
	int printed;

	printed = 0;
	if (prm.plus)
		printed += write(1, "+", 1);
	else if (prm.space)
		printed += write(1, " ", 1);
	while (prm.width > 0)
	{
		printed += write(1, "0", 1);
		prm.width--;
	}
	while (l)
	{
		ft_putchar(n / l + '0');
		n %= l;
		l /= 10;
		printed++;
	}
	return (printed);
}

static int	print_nof(unsigned long long n, unsigned long long l, t_frmt prm)
{
	int printed;

	printed = 0;
	while (prm.width > 0)
	{
		printed += write(1, " ", 1);
		prm.width--;
	}
	if (prm.plus)
		printed += write(1, "+", 1);
	else if (prm.space)
		printed += write(1, " ", 1);
	while (prm.precision > 0)
	{
		printed += write(1, "0", 1);
		prm.precision--;
	}
	while (l)
	{
		ft_putchar(n / l + '0');
		n %= l;
		l /= 10;
		printed++;
	}
	return (printed);
}

static int	print_number(unsigned long long n, t_frmt params)
{
	unsigned long long length;

	if (params.precision >= 0)
		params.zero = 0;
	params.precision--;
	params.width--;
	length = 1;
	while (n / 10 >= length)
	{
		length *= 10;
		params.width--;
		params.precision--;
	}
	if (params.precision > 0)
		params.width -= params.precision;
	if (params.plus || params.space)
		params.width--;
	if (params.minus)
		return (print_minusf(n, length, params));
	else if (params.zero)
		return (print_zerof(n, length, params));
	else
		return (print_nof(n, length, params));
}

int			print_unsigned(void *argp, t_frmt params)
{
	if (params.mod == HH)
		return (print_number((unsigned char)argp, params));
	else if (params.mod == H)
		return (print_number((unsigned short)argp, params));
	else if (params.mod == L)
		return (print_number((unsigned long)argp, params));
	else if (params.mod == LL)
		return (print_number((unsigned long long)argp, params));
	return (print_number((unsigned int)argp, params));
}
