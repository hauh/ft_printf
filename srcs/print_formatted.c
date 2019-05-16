/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:02:25 by smorty            #+#    #+#             */
/*   Updated: 2019/05/16 23:27:54 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_formatted(va_list argp, t_frmt *params)
{
	if ((*params).spec == 'd' || (*params).spec == 'i' || (*params).spec == 'D')
		process_d(argp, params);
	if ((*params).spec == 'u' || (*params).spec == 'U')
		process_u(argp, params);
	if ((*params).spec == 'o' || (*params).spec == 'O')
		process_o(argp, params);
	if ((*params).spec == 'x' || (*params).spec == 'X' || (*params).spec == 'p')
		process_x(argp, params);
	if ((*params).spec == 'b' || (*params).spec == 'B')
		process_b(argp, params);
	if (S_REA((*params).spec))
	{
		if ((*params).mod == LD)
			process_feg(va_arg(argp, long double), params);
		else
			process_feg(va_arg(argp, double), params);
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