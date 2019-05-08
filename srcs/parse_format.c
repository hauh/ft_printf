/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:11:46 by smorty            #+#    #+#             */
/*   Updated: 2019/05/07 21:58:37 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	initialize_struct(t_frmt *params)
{
	(*params).minus = 0;
	(*params).plus = 0;
	(*params).space = 0;
	(*params).hash = 0;
	(*params).zero = 0;
	(*params).mod = 0;
	(*params).width = -1;
	(*params).precision = -1;
	(*params).spec = 0;
}

static void	get_flag(const char **format, t_frmt *params)
{
	if (**format == '-')
		(*params).minus = 1;
	else if (**format == '+')
		(*params).plus = 1;
	else if (**format == ' ')
		(*params).space = 1;
	else if (**format == '#')
		(*params).hash = 1;
	else if (**format == '0' && !ft_isdigit(*(*format - 1)))
		(*params).zero = 1;
	(*format)++;
}

static void	get_mod(const char **format, t_frmt *params)
{
	if (**format == 'h')
	{
		if (*(*format + 1) == 'h')
		{
			(*format)++;
			if ((*params).mod < HH)
				(*params).mod = HH;
		}
		else if ((*params).mod < H)
			(*params).mod = H;
	}
	else if (**format == 'l')
	{
		if (*(*format + 1) == 'l')
		{
			(*format)++;
			if ((*params).mod < LL)
				(*params).mod = LL;
		}
		else if ((*params).mod < L) 
			(*params).mod = L;
	}
	else if (**format == 'z' && (*params).mod < Z)
		(*params).mod = Z;
	else
		(*params).mod = J;
	(*format)++;
}

int			parse_format(const char **format, va_list argp)
{
	t_frmt params;

	initialize_struct(&params);
	while (!SPEC(**format))
	{
		if (FLAG(**format))
			get_flag(format, &params);
		else if (ft_isdigit(**format) && **format != '0')
		{
			params.width = ft_atoi(*format);
			while (ft_isdigit(**format))
				(*format)++;
		}
		else if (**format == '.')
		{
			(*format)++;
			params.precision = ft_atoi(*format);
			while (ft_isdigit(**format))
				(*format)++;
		}
		else if (MOD(**format))
			get_mod(format, &params);
		else if (**format == 0)
		{
			(*format)--;
			return (0);
		}
		else
			return (print_char(**format, &params));
	}
	params.spec = **format;
	if (**format == 'U')
		params.mod = L;
	return (print_formatted(argp, &params));
}