/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:25:04 by smorty            #+#    #+#             */
/*   Updated: 2019/05/15 20:27:54 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		num_len(intmax_t n)
{
	intmax_t	d;
	int			size;

	if (!n)
		return (0);
	size = 1;
	n /= (n < 0 ? -10 : 10);
	d = 1;
	while (d <= n)
	{
		d *= 10;
		size++;
	}
	return (size);
}

void	ntoa(char *s, intmax_t n)
{
	if (n < 0)
	{
		s--;
		*s = n % 10 * -1 + '0';
		n /= 10;
		n *= -1;
	}
	while (n)
	{
		s--;
		*s = n % 10 + '0';
		n /= 10;
	}
}

char *get_width(t_frmt *prm)
{
	char *width;

	prm->width -= prm->len;
	if (!(width = (char *)malloc(sizeof(char) * (prm->width + 1))))
		return (NULL);
	ft_memset(width, (prm->flags & F_ZERO ? '0' : ' '), prm->width);
	*(width + prm->width) = 0;
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

void print(char *out, char *width, t_frmt *prm)
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