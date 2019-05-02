/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:42:26 by smorty            #+#    #+#             */
/*   Updated: 2019/05/02 22:51:06 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_flag_minus(int **rev, int len, t_formatted to_print)
{
	int printed;

	printed = 0;
	if (**rev < 0)
		printed += write(1, "-", 1);
	else if (to_print.plus)
		printed += write(1, "+", 1);
	else if (to_print.space)
		printed += write(1, " ", 1);
	to_print.width -= len;
	while (len)
	{
		ft_putchar((*rev)[len] + '0');
		len--;
		printed++;
	}
	while (to_print.width > 0)
	{
		printed += write(1, " ", 1);
		to_print.width--;
	}
	free(*rev);
	return (printed);
}

static int	print_flag_zero(int **rev, int len, t_formatted to_print)
{
	int printed;

	printed = 0;
	if (**rev < 0)
		printed += write(1, "-", 1);
	else if (to_print.plus)
		printed += write(1, "+", 1);
	else if (to_print.space)
		printed += write(1, " ", 1);
	while (len < to_print.width)
	{
		printed += write(1, "0", 1);
		to_print.width--;
	}
	while (len)
	{
		ft_putchar((*rev)[len] + '0');
		len--;
		printed++;
	}
	free(*rev);
	return (printed);
}

static int	print_flagless(int **rev, int len, t_formatted to_print)
{
	int printed;

	printed = 0;
	while (len < to_print.width)
	{
		printed += write(1, " ", 1);
		to_print.width--;
	}
	if (**rev < 0)
		printed += write(1, "-", 1);
	else if (to_print.plus)
		printed += write(1, "+", 1);
	else if (to_print.space)
		printed += write(1, " ", 1);
	while (len)
	{
		ft_putchar((*rev)[len] + '0');
		len--;
		printed++;
	}
	free(*rev);
	return (printed);
}

static int	*split_number(long long n, int len)
{
	int i;
	int *rev;

	rev = (int *)malloc(sizeof(int) * (len + 1));
	if (!rev)
		return (NULL);
	rev[0] = (n < 0 ? -1 : 1);
	if (!n)
		rev[1] = 0;
	else
	{
		i = 1;
		while (n)
		{
			rev[i] = (n < 0 ? n % 10 * -1 : n % 10);
			n /= 10;
			i++;
		}
	}
	return (rev);
}

int			print_ints(long long n, t_formatted to_print)
{
	long long	tmp;
	int			*rev;
	int			len;

	len = (n ? 0 : 1);
	tmp = n;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	rev = split_number(n, len);
	if (!rev)
		return (-1);
	if (to_print.plus || to_print.space || rev[0] < 0)
		to_print.width--;
	if (to_print.minus)
		return (print_flag_minus(&rev, len, to_print));
	else if (to_print.zero)
		return (print_flag_zero(&rev, len, to_print));
	else
		return (print_flagless(&rev, len, to_print));
}
