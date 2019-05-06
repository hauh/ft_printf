/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:02:25 by smorty            #+#    #+#             */
/*   Updated: 2019/05/06 20:44:22 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_formatted_di(va_list argp, t_frmt *params)
{
	if ((*params).mod == HH)
		return (print_di((char)va_arg(argp, int), params));
	else if ((*params).mod == H)
		return (print_di((short)va_arg(argp, int), params));
	else if ((*params).mod == NO)
		return (print_di(va_arg(argp, int), params));
	else if ((*params).mod == L)
		return (print_di(va_arg(argp, long), params));
	else if ((*params).mod == LL)
		return (print_di(va_arg(argp, long long), params));
	else if ((*params).mod == J)
		return (print_di(va_arg(argp, intmax_t), params));
	else if ((*params).mod == Z)
		return (print_di(va_arg(argp, ssize_t), params));
	else
		return (-1);
}

static int	print_formatted_u(va_list argp, t_frmt *params)
{
	if ((*params).mod == HH)
		return (print_u((unsigned char)va_arg(argp, unsigned int), params));
	else if ((*params).mod == H)
		return (print_u((unsigned short)va_arg(argp, unsigned int), params));
	else if ((*params).mod == NO)
		return (print_u(va_arg(argp, unsigned int), params));
	else if ((*params).mod == L)
		return (print_u(va_arg(argp, unsigned long), params));
	else if ((*params).mod == LL)
		return (print_u(va_arg(argp, unsigned long long), params));
	else if ((*params).mod == J)
		return (print_u(va_arg(argp, uintmax_t), params));
	else if ((*params).mod == Z)
		return (print_u(va_arg(argp, size_t), params));
	else
		return (-1);
}

static int	print_formatted_o(va_list argp, t_frmt *params)
{
	if ((*params).mod == HH)
		return (print_o((unsigned char)va_arg(argp, unsigned int), params));
	else if ((*params).mod == H)
		return (print_o((unsigned short)va_arg(argp, unsigned int), params));
	else if ((*params).mod == NO)
		return (print_o(va_arg(argp, unsigned int), params));
	else if ((*params).mod == L)
		return (print_o(va_arg(argp, unsigned long), params));
	else if ((*params).mod == LL)
		return (print_o(va_arg(argp, unsigned long long), params));
	else if ((*params).mod == J)
		return (print_o(va_arg(argp, uintmax_t), params));
	else if ((*params).mod == Z)
		return (print_o(va_arg(argp, size_t), params));
	else
		return (-1);
}

static int	print_formatted_base(va_list argp, t_frmt *params, int base)
{
	if ((*params).mod == HH)
		return (print_base((unsigned char )va_arg(argp, unsigned int), params, base));
	else if ((*params).mod == H)
		return (print_base((unsigned short)va_arg(argp, unsigned int), params, base));
	else if ((*params).mod == NO)
		return (print_base(va_arg(argp, unsigned int), params, base));
	else if ((*params).mod == L)
		return (print_base(va_arg(argp, unsigned long), params, base));
	else if ((*params).mod == LL)
		return (print_base(va_arg(argp, unsigned long long), params, base));
	else if ((*params).mod == J)
		return (print_base(va_arg(argp, uintmax_t), params, base));
	else if ((*params).mod == Z)
		return (print_base(va_arg(argp, size_t), params, base));
	else
		return (-1);
}

int			print_formatted(va_list argp, t_frmt *params)
{
	if ((*params).spec == 'd' || (*params).spec == 'i')
		return (print_formatted_di(argp, params));
	if ((*params).spec == 'u' || (*params).spec == 'U')
		return (print_formatted_u(argp, params));
	else if ((*params).spec == 'o')
		return (print_formatted_o(argp, params));
	else if ((*params).spec == 'x' || (*params).spec == 'X')
		return (print_formatted_base(argp, params, 16));
	else if ((*params).spec == 'c')
		return (print_char((const char)va_arg(argp, int), params));
	else if ((*params).spec == 's')
		return (print_string(va_arg(argp, const char *), params));
	else
		return (-1);	
}