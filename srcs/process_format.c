/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:02:25 by smorty            #+#    #+#             */
/*   Updated: 2019/05/31 18:04:45 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	process_n(int *p)
{
	print_buf();
	if (!p)
		return (g_ftprintf.error = -1);
	*p = g_ftprintf.printed;
	return (0);
}

int			process_format(va_list *argp, t_frmt *prm)
{
	if (S_CHA(prm->spec))
		return (process_cs(argp, prm));
	else if (S_REA(prm->spec))
		return (process_float(argp, prm));
	else
	{
		if ((prm->flags & (F_ZERO | F_PREC)) == (F_ZERO | F_PREC))
			prm->flags ^= F_ZERO;
		if (prm->spec == 'd' || prm->spec == 'i' || prm->spec == 'D')
			return (process_d(argp, prm));
		else if (prm->spec == 'u' || prm->spec == 'U')
			return (process_u(argp, prm));
		else if (prm->spec == 'o' || prm->spec == 'O')
			return (process_o(argp, prm));
		else if (prm->spec == 'x' || prm->spec == 'X' || prm->spec == 'p')
			return (process_x(argp, prm));
		else if (prm->spec == 'b' || prm->spec == 'B')
			return (process_b(argp, prm));
		else if (prm->spec == 'n')
			return (process_n(va_arg(*argp, int *)));
	}
	return (g_ftprintf.error = -1);
}
