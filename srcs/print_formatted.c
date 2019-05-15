/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:02:25 by smorty            #+#    #+#             */
/*   Updated: 2019/05/15 21:04:43 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_formatted_di(va_list argp, t_frmt *params)
{
	if ((*params).mod == HH)
		print_d((char)va_arg(argp, int), params);
	if ((*params).mod == H)
		print_d((short)va_arg(argp, int), params);
	if ((*params).mod == NO)
		print_d(va_arg(argp, int), params);
	if ((*params).mod == L)
		print_d(va_arg(argp, long), params);
	if ((*params).mod == LL)
		print_d(va_arg(argp, long long), params);
	if ((*params).mod == Z)
		print_d(va_arg(argp, ssize_t), params);
	if ((*params).mod == J)
		print_d(va_arg(argp, intmax_t), params);
}

static void	print_formatted_u(va_list argp, t_frmt *params)
{
	if ((*params).mod == HH)
		print_u((unsigned char)va_arg(argp, unsigned int), params);
	if ((*params).mod == H)
		print_u((unsigned short)va_arg(argp, unsigned int), params);
	if ((*params).mod == NO)
		print_u(va_arg(argp, unsigned int), params);
	if ((*params).mod == L)
		print_u(va_arg(argp, unsigned long), params);
	if ((*params).mod == LL)
		print_u(va_arg(argp, unsigned long long), params);
	if ((*params).mod == Z)
		print_u(va_arg(argp, size_t), params);
	if ((*params).mod == J)
		print_u(va_arg(argp, uintmax_t), params);
}

static void	print_formatted_o(va_list argp, t_frmt *params)
{
	if ((*params).mod == HH)
		print_o((unsigned char)va_arg(argp, unsigned int), params);
	if ((*params).mod == H)
		print_o((unsigned short)va_arg(argp, unsigned int), params);
	if ((*params).mod == NO)
		print_o(va_arg(argp, unsigned int), params);
	if ((*params).mod == L)
		print_o(va_arg(argp, unsigned long), params);
	if ((*params).mod == LL)
		print_o(va_arg(argp, unsigned long long), params);
	if ((*params).mod == Z)
		print_o(va_arg(argp, size_t), params);
	if ((*params).mod == J)
		print_o(va_arg(argp, uintmax_t), params);
}

static void	print_formatted_x(va_list argp, t_frmt *params)
{
	if ((*params).mod == HH)
		print_x((unsigned char)va_arg(argp, unsigned int), params);
	if ((*params).mod == H)
		print_x((unsigned short)va_arg(argp, unsigned int), params);
	if ((*params).mod == NO)
		print_x(va_arg(argp, unsigned int), params);
	if ((*params).mod == L)
		print_x(va_arg(argp, unsigned long), params);
	if ((*params).mod == LL)
		print_x(va_arg(argp, unsigned long long), params);
	if ((*params).mod == Z)
		print_x(va_arg(argp, size_t), params);
	if ((*params).mod == J)
		print_x(va_arg(argp, uintmax_t), params);
}

static void	print_formatted_b(va_list argp, t_frmt *params)
{
	if ((*params).mod == HH)
		print_b((unsigned char)va_arg(argp, unsigned int), params);
	if ((*params).mod == H)
		print_b((unsigned short)va_arg(argp, unsigned int), params);
	if ((*params).mod == NO)
		print_b(va_arg(argp, unsigned int), params);
	if ((*params).mod == L)
		print_b(va_arg(argp, unsigned long), params);
	if ((*params).mod == LL)
		print_b(va_arg(argp, unsigned long long), params);
	if ((*params).mod == Z)
		print_b(va_arg(argp, size_t), params);
	if ((*params).mod == J)
		print_b(va_arg(argp, uintmax_t), params);
}

void			print_formatted(va_list argp, t_frmt *params)
{
	if ((*params).spec == 'd' || (*params).spec == 'i' || (*params).spec == 'D')
		print_formatted_di(argp, params);
	if ((*params).spec == 'u' || (*params).spec == 'U')
		print_formatted_u(argp, params);
	if ((*params).spec == 'o' || (*params).spec == 'O')
		print_formatted_o(argp, params);
	if ((*params).spec == 'x' || (*params).spec == 'X')
		print_formatted_x(argp, params);
	if ((*params).spec == 'b' || (*params).spec == 'B')
		print_formatted_b(argp, params);
	if ((*params).spec == 'p')
	{
		(*params).flags |= F_HASH;
		print_x(va_arg(argp, intptr_t), params);
	}
	if (S_REA((*params).spec))
	{
		if ((*params).mod == LD)
			print_feg(va_arg(argp, long double), params);
		else
			print_feg(va_arg(argp, double), params);
	}
	if ((*params).spec == 'c' || (*params).spec == 'C')
	{
		if ((*params).mod == L || (*params).mod == LL || (*params).spec == 'C')
			print_c((const wchar_t)va_arg(argp, int), params);
		else
			print_c((const char)va_arg(argp, int), params);
	}
	if ((*params).spec == 's' || (*params).spec == 'S')
	{
		if ((*params).mod == L || (*params).mod == LL || (*params).spec == 'S')
			print_ws(va_arg(argp, wchar_t *), params);
		else
			print_s(va_arg(argp, char *), params);
	}
}