/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:11:46 by smorty            #+#    #+#             */
/*   Updated: 2019/05/02 23:06:11 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialize_struct(t_formatted *to_print)
{
	(*to_print).minus = 0;
	(*to_print).plus = 0;
	(*to_print).space = 0;
	(*to_print).hash = 0;
	(*to_print).zero = 0;
	(*to_print).mod = 0;
	(*to_print).width = -1;
	(*to_print).percision = -1;
}

void	store_flag(const char **format, t_formatted *to_print)
{
	if (**format == '-')
		(*to_print).minus = 1;
	else if (**format == '+')
		(*to_print).plus = 1;
	else if (**format == ' ')
		(*to_print).space = 1;
	else if (**format == '#')
		(*to_print).hash = 1;
	else if (**format == '0')
		(*to_print).zero = 1;
	(*format)++;
}

void	store_mod(const char **format, t_formatted *to_print)
{
	if (**format == 'h')
	{
		(*format)++;
		if (**format == 'h')
		{
			(*to_print).mod = HH;
			(*format)++;
		}
		else
			(*to_print).mod = H;
	}
	else
	{
		(*format)++;
		if (**format == 'l')
		{
			(*to_print).mod = LL;
			(*format)++;
		}
		else
			(*to_print).mod = L;
	}
}

void	store_width(const char **format, t_formatted *to_print)
{
	(*to_print).width = ft_atoi(*format);
	while (ft_isdigit(**format))
		(*format)++;
}

void	store_percision(const char **format, t_formatted *to_print)
{
	(*format)++;
	(*to_print).percision = ft_atoi(*format);
	while (ft_isdigit(**format))
		(*format)++;
}