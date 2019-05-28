/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:02:25 by smorty            #+#    #+#             */
/*   Updated: 2019/05/28 15:23:45 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	process_n(int *p)
{
	print_buf();
	*p = g_printed;
}

void		process_format(va_list *argp, t_frmt *prm)
{
	if (prm->spec == 'd' || prm->spec == 'i' || prm->spec == 'D')
		process_d(argp, prm);
	else if (prm->spec == 'u' || prm->spec == 'U')
		process_u(argp, prm);
	else if (prm->spec == 'o' || prm->spec == 'O')
		process_o(argp, prm);
	else if (prm->spec == 'x' || prm->spec == 'X' || prm->spec == 'p')
		process_x(argp, prm);
	else if (prm->spec == 'b' || prm->spec == 'B')
		process_b(argp, prm);
	else if (S_CHA(prm->spec))
		process_cs(argp, prm);
	else if (S_REA(prm->spec))
		process_float(argp, prm);
	else if (prm->spec == 'n')
		process_n(va_arg(*argp, int *));
}
