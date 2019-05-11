/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:11:46 by smorty            #+#    #+#             */
/*   Updated: 2019/05/11 22:49:15 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	initialize_struct(t_frmt *params)
{
	(*params).flags = 0;
	(*params).mod = 0;
	(*params).width = 0;
	(*params).precision = 1;
	(*params).spec = 0;
	(*params).fd = 1;
}

static void	get_flag(const char **format, int *flags)
{
	if (**format == '-')
		*flags |= F_MINUS;
	else if (**format == '+')
		*flags |= F_PLUS;
	else if (**format == ' ')
		*flags |= F_SPACE;
	else if (**format == '#')
		*flags |= F_HASH;
	else if (**format == '0' && !ft_isdigit(*(*format - 1)))
		*flags |= F_ZERO;
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
			get_flag(format, &params.flags);
		else if (ft_isdigit(**format) && **format != '0')
		{
			params.width = ft_atoi(*format);
			while (ft_isdigit(**format))
				(*format)++;
		}
		else if (**format == '.')
		{
			(*format)++;
			params.flags |= F_PREC;
			params.precision = ft_atoi(*format) + 1;
			while (ft_isdigit(**format))
				(*format)++;
		}
		else if (**format == '*')
		{
			if (*(*format - 1) == '.')
			{
				params.flags |= F_PREC;
				params.precision = va_arg(argp, int) + 1;
				(*format)++;
			}
			else
			{
				params.width = va_arg(argp, int);
				if (params.width < 0)
				{
					params.width = ~params.width + 1;
					params.flags |= F_MINUS;
				}
				(*format)++;
			}
		}
		else if (MOD(**format))
			get_mod(format, &params);
		else if (**format == 0)
		{
			(*format)--;
			return (0);
		}
		else
			return (print_c(**format, &params));
	}
	params.spec = **format;
	if (**format == 'D' || **format == 'U' || **format == 'O')
		params.mod = J;
	return (print_formatted(argp, &params));
}