/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:01:27 by smorty            #+#    #+#             */
/*   Updated: 2019/05/02 23:08:20 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_number(t_formatted to_print, void *argp)
{
	if (to_print.mod == HH)
		return(print_ints((char)argp, to_print));
	else if (to_print.mod == H)
		return(print_ints((short)argp, to_print));
	else if (to_print.mod == L)
		return(print_ints((long)argp, to_print));
	else if (to_print.mod == LL)
		return(print_ints((long long)argp, to_print));
	return(print_ints((int)argp, to_print));
}