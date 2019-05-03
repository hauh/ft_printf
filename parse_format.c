/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 16:11:46 by smorty            #+#    #+#             */
/*   Updated: 2019/05/03 23:01:47 by smorty           ###   ########.fr       */
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
			(*params).mod = HH;
		}
		else
			(*params).mod = H;
	}
	else
	{
		if (*(*format + 1) == 'l')
		{
			(*format)++;
			(*params).mod = LL;
		}
		else
			(*params).mod = L;
	}
	(*format)++;
}

static int		print_formatted(t_frmt params, va_list argp)
{
	if (params.spec == 'd' || params.spec == 'i')
		return (print_integers(va_arg(argp, void *), params));
	if (params.spec == 'u')
		return (print_unsigned(va_arg(argp, void *), params));
//	else if (S_816(params.spec))
//		print_816(params, argp);
//	else if (S_REA(params.spec))
//		print_real(params, argp);
	else if (S_CHA(params.spec))
		return (print_chars(va_arg(argp, void *), params));
//	else if (params.spec == 'p')
//		print_pointer(params, argp);
	return (0);
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
		else if (**format == 'h' || **format == 'l')
			get_mod(format, &params);
		else
			return (print_chars((void *)*format, params));
	}
	params.spec = **format;
	return (print_formatted(params, argp));
}
