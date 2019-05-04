/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:02:25 by smorty            #+#    #+#             */
/*   Updated: 2019/05/04 17:47:56 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_formatted_integers(va_list argp, t_frmt params, int base)
{
	if (params.mod == HH)
		return (print_number_base(va_arg(argp, char), params, base));
	else if (params.mod == H)
		return (print_number_base(va_arg(argp, short), params, base));
	else if (params.mod == NO)
		return (print_number_base(va_arg(argp, int), params, base));
	else if (params.mod == L)
		return (print_number_base(va_arg(argp, long), params, base));
	else if (params.mod == LL)
		return (print_number_base(va_arg(argp, long long), params, base));
	else
		return (-1);
}

static int	print_formatted_unsigned(va_list argp, t_frmt params, int base)
{
	if (params.mod == HH)
		return (print_number_base_u(va_arg(argp, unsigned char), params, base));
	else if (params.mod == H)
		return (print_number_base_u(va_arg(argp, unsigned short), params, base));
	else if (params.mod == NO)
		return (print_number_base_u(va_arg(argp, unsigned int), params, base));
	else if (params.mod == L)
		return (print_number_base_u(va_arg(argp, unsigned long), params, base));
	else if (params.mod == LL)
		return (print_number_base_u(va_arg(argp, unsigned long long), params, base));
	else
		return (-1);
}

int			print_formatted(va_list argp, t_frmt params)
{
	if (params.spec == 'd' || params.spec == 'i')
		return (print_formatted_integers(argp, params, 10));
	if (params.spec == 'u')
		return (print_formatted_unsigned(argp, params, 10));
	else if (params.spec == 'o')
		return (print_formatted_unsigned(argp, params, 8));
	else if (params.spec == 'x' || params.spec == 'X')
		return (print_formatted_unsigned(argp, params, 16));
	else if (params.spec == 'c')
		return (print_char(va_arg(argp, const char), params));
	else if (params.spec == 's')
		return (print_string(va_arg(argp, const char *), params));
	else
		return (-1);	
}