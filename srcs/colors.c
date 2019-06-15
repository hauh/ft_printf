/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:37:46 by smorty            #+#    #+#             */
/*   Updated: 2019/06/15 20:18:28 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	set_color(char *color, int color_len)
{
	if (BUFF_SIZE >= color_len)
	{
		CHECK_BUFF(color_len);
		string_to_buf(color, color + color_len);
		return (color_len);
	}
	char_to_buf('{', 1);
	return (1);
}

void		check_color_and_fd(const char **format, va_list *argp)
{
	if (ft_strnequ(*format, "{red}", 5))
		*format += set_color(COLOR_RED, 5);
	else if (ft_strnequ(*format, "{green}", 7))
		*format += set_color(COLOR_GREEN, 5);
	else if (ft_strnequ(*format, "{yellow}", 8))
		*format += set_color(COLOR_YELLOW, 5);
	else if (ft_strnequ(*format, "{blue}", 6))
		*format += set_color(COLOR_BLUE, 5);
	else if (ft_strnequ(*format, "{magenta}", 9))
		*format += set_color(COLOR_MAGENTA, 5);
	else if (ft_strnequ(*format, "{cyan}", 6))
		*format += set_color(COLOR_CYAN, 5);
	else if (ft_strnequ(*format, "{eoc}", 5))
		*format += set_color(COLOR_RESET, 4);
	else if (ft_strnequ(*format, "{*}", 3))
	{
		print_buf();
		g_ftprintf.fd = va_arg(*argp, int);
		*format += 3;
	}
	else
	{
		char_to_buf('{', 1);
		++(*format);
	}
}
