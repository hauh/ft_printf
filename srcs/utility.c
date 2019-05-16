/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:25:04 by smorty            #+#    #+#             */
/*   Updated: 2019/05/16 23:28:40 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *get_width(t_frmt *prm)
{
	char *width;

	width = NULL;
	if (prm->width > prm->len)
	{
		prm->width -= prm->len;
		if (!(width = (char *)malloc(sizeof(char) * (prm->width + 1))))
		{
			g_error = -1;
			return (NULL);
		}
		ft_memset(width, (prm->flags & F_ZERO ? '0' : ' '), prm->width);
		*(width + prm->width) = 0;
	}
	return (width);
}

void move_to_buf(char *s)
{
	while (*s)
	{
		*(g_buf + g_len) = *s;
		++s;
		++g_len;
		if (g_len == BUFF_SIZE)
			print_buf();
	}
}

void to_print(char *out, char *width, t_frmt *prm)
{
	if (!(prm->flags & F_MINUS) && width)
	{
		move_to_buf(width);
		free(width);
	}
	if (out)
	{
		*(out + prm->len) = 0;
		move_to_buf(out);
		free(out);
	}
	if ((prm->flags & F_MINUS) && width)
	{
		move_to_buf(width);
		free(width);
	}
}