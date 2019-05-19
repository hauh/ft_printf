/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:02:25 by smorty            #+#    #+#             */
/*   Updated: 2019/05/19 23:11:03 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_formatted(va_list argp, t_frmt *prm)
{
	if (prm->spec == 'd' || prm->spec == 'i' || prm->spec == 'D')
		process_d(argp, prm);
	if (prm->spec == 'u' || prm->spec == 'U')
		process_u(argp, prm);
	if (prm->spec == 'o' || prm->spec == 'O')
		process_o(argp, prm);
	if (prm->spec == 'x' || prm->spec == 'X' || prm->spec == 'p')
		process_x(argp, prm);
	if (prm->spec == 'b' || prm->spec == 'B')
		process_b(argp, prm);
	if (S_REA(prm->spec))
	{
		if (prm->flags & F_LONGD)
			process_feg(va_arg(argp, long double), prm);
		else
			process_feg(va_arg(argp, double), prm);
	}
	if (prm->spec == 'c' || prm->spec == 'C')
	{
		if (prm->mod == L || prm->mod == LL || prm->spec == 'C')
			print_c((const wchar_t)va_arg(argp, int), prm);
		else
			print_c((const char)va_arg(argp, int), prm);
	}
	if (prm->spec == 's' || prm->spec == 'S')
	{
		if (prm->mod == L || prm->mod == LL || prm->spec == 'S')
			print_ws(va_arg(argp, wchar_t *), prm);
		else
			print_s(va_arg(argp, char *), prm);
	}
}
