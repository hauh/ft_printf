/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:25:04 by smorty            #+#    #+#             */
/*   Updated: 2019/05/24 22:03:05 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_buf(void)
{
	int printed;

	printed = write(g_fd, g_buf, g_len);
	if (printed < 0)
		g_error = -1;
	else
		g_printed += printed;
	g_len = 0;
}

void	char_to_buf(char c, int n)
{
	while (n)
	{
		*(g_buf + g_len) = c;
		++g_len;
		if (g_len == BUFF_SIZE)
			print_buf();
		--n;
	}
}

void	string_to_buf(char *s)
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

char	*make_width(t_frmt *prm)
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

void	to_print(char *out, char *width, t_frmt *prm)
{
	if (!(prm->flags & F_MINUS) && width)
	{
		string_to_buf(width);
		free(width);
	}
	string_to_buf(out);
	if ((prm->flags & F_MINUS) && width)
	{
		string_to_buf(width);
		free(width);
	}
}
