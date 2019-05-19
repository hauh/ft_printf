/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:37:46 by smorty            #+#    #+#             */
/*   Updated: 2019/05/19 19:45:18 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	set_color(char *color, int color_len)
{
	if (BUFF_SIZE >= color_len)
	{
		CHECK_BUFF(color_len);
		while (*color)
		{
			*(g_buf + g_len) = *color;
			++g_len;
			++color;
		}
		if (g_len == BUFF_SIZE)
			print_buf();
		return (color_len);
	}
	return (0);
}

void		check_color(const char **format)
{
	if (ft_strnequ(*format, "{red}", 5))
		*format += set_color(COLOR_RED, 5);
	else if (ft_strnequ(*format, "{green}", 7))
		*format += set_color(COLOR_GREEN, 7);
	else if (ft_strnequ(*format, "{yellow}", 8))
		*format += set_color(COLOR_YELLOW, 8);
	else if (ft_strnequ(*format, "{blue}", 6))
		*format += set_color(COLOR_BLUE, 6);
	else if (ft_strnequ(*format, "{magenta}", 9))
		*format += set_color(COLOR_MAGENTA, 9);
	else if (ft_strnequ(*format, "{cyan}", 6))
		*format += set_color(COLOR_CYAN, 6);
	else if (ft_strnequ(*format, "{eoc}", 5))
		*format += set_color(COLOR_RESET, 5);
	else
	{
		char_to_buf('{');
		++(*format);
	}
}
