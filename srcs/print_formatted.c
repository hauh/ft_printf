/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:02:25 by smorty            #+#    #+#             */
/*   Updated: 2019/05/12 21:22:41 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_formatted_di(va_list argp, t_frmt *params)
{
	if ((*params).mod == HH)
		return (print_d((char)va_arg(argp, int), params));
	else if ((*params).mod == H)
		return (print_d((short)va_arg(argp, int), params));
	else if ((*params).mod == NO)
		return (print_d(va_arg(argp, int), params));
	else if ((*params).mod == L)
		return (print_d(va_arg(argp, long), params));
	else if ((*params).mod == LL)
		return (print_d(va_arg(argp, long long), params));
	else if ((*params).mod == Z)
		return (print_d(va_arg(argp, ssize_t), params));
	else if ((*params).mod == J)
		return (print_d(va_arg(argp, intmax_t), params));
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
	else if ((*params).mod == Z)
		return (print_u(va_arg(argp, size_t), params));
	else if ((*params).mod == J)
		return (print_u(va_arg(argp, uintmax_t), params));
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
	else if ((*params).mod == Z)
		return (print_o(va_arg(argp, size_t), params));
	else if ((*params).mod == J)
		return (print_o(va_arg(argp, uintmax_t), params));
	else
		return (-1);
}

static int	print_formatted_x(va_list argp, t_frmt *params)
{
	if ((*params).mod == HH)
		return (print_x((unsigned char )va_arg(argp, unsigned int), params));
	else if ((*params).mod == H)
		return (print_x((unsigned short)va_arg(argp, unsigned int), params));
	else if ((*params).mod == NO)
		return (print_x(va_arg(argp, unsigned int), params));
	else if ((*params).mod == L)
		return (print_x(va_arg(argp, unsigned long), params));
	else if ((*params).mod == LL)
		return (print_x(va_arg(argp, unsigned long long), params));
	else if ((*params).mod == Z)
		return (print_x(va_arg(argp, size_t), params));
	else if ((*params).mod == J)
		return (print_x(va_arg(argp, uintmax_t), params));
	else
		return (-1);
}

int			print_formatted(va_list argp, t_frmt *params)
{
	if ((*params).spec == 'd' || (*params).spec == 'i' || (*params).spec == 'D')
		return (print_formatted_di(argp, params));
	if ((*params).spec == 'u' || (*params).spec == 'U')
		return (print_formatted_u(argp, params));
	if ((*params).spec == 'o' || (*params).spec == 'O')
		return (print_formatted_o(argp, params));
	if ((*params).spec == 'x' || (*params).spec == 'X')
		return (print_formatted_x(argp, params));
	if ((*params).spec == 'p')
	{
		(*params).flags |= F_HASH;
		return (print_x(va_arg(argp, intptr_t), params));
	}
	if (S_REA((*params).spec))
	{
		if (!((*params).flags & F_PREC))
			(*params).precision = 6;
		if ((*params).mod == LD)
			return (print_feg(va_arg(argp, long double), params));
		return (print_feg(va_arg(argp, double), params));
	}
	if ((*params).spec == 'c' || (*params).spec == 'C')
	{
		if ((*params).mod == L || (*params).mod == LL || (*params).spec == 'C')
			return (print_c((const wchar_t)va_arg(argp, int), params));
		return (print_c((const char)va_arg(argp, int), params));
	}
	if ((*params).spec == 's' || (*params).spec == 'S')
	{
		if ((*params).mod == L || (*params).mod == LL || (*params).spec == 'S')
			return (print_ws((const wchar_t *)va_arg(argp, const wchar_t *), params));	
		return (print_s(va_arg(argp, const char *), params));
	}
	return (-1);	
}