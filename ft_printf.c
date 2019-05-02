/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:55:41 by smorty            #+#    #+#             */
/*   Updated: 2019/05/02 23:08:52 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_formatted(t_formatted to_print, void *argp)
{
	if (S_NUM(to_print.spec))
		print_number(to_print, argp);
//	else if (S_816(to_print.spec))
//		print_816(to_print, argp);
//	else if (S_REA(to_print.spec))
//		print_real(to_print, argp);
//	else if (S_CHA(to_print.spec))
//		print_char(to_print, argp);
//	else if (to_print.spec == 'p')
//		print_pointer(to_print, argp);
}

void	parse_format(const char **format, void *argp)
{
	t_formatted to_print;

	initialize_struct(&to_print);
	while (FLAG(**format))
		store_flag(format, &to_print);
	if (ft_isdigit(**format))
		store_width(format, &to_print);
	if (**format == '.')
		store_percision(format, &to_print);
	if (**format == 'h' || **format == 'l')
		store_mod(format, &to_print);
	to_print.spec = **format;
	print_formatted(to_print, argp);
}

int		ft_printf(const char *format, ...)
{
	va_list argp;

	va_start(argp, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '%')
				write(1, "%", 1);
			else
				parse_format(&format, va_arg(argp, void *));
		}
		else
			write(1, format, 1);
		format++;
	}
	va_end(argp);
	return(0);
}

#include <stdio.h>
int main(void)
{
	int n;

	ft_printf("%+0123hhd<\n", -2222222333333322222);
	printf("%+0123hhd%n<\n", -2222222333333322222, &n);
	printf("%d", n);
}