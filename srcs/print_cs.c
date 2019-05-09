/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:49:39 by smorty            #+#    #+#             */
/*   Updated: 2019/05/09 20:32:36 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(const char argc, t_frmt *params)
{
	char	*s;
	int		printed;
	int		size;
	int		flags;

	flags = (*params).flags;
	if (flags & F_ZERO && flags & F_MINUS)
		flags ^= F_ZERO;
	size = MAX((*params).width, 1);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	*(s + size) = 0;
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	if (flags & F_MINUS)
		*s = argc;
	else
		*(s + size - 1) = argc;
	printed = write(1, s, size);
	free(s);
	return (printed);
}

int	print_s(const char *args, t_frmt *params)
{
	char	*s;
	int		printed;
	int		size;
	int		len;
	int		flags;

	flags = (*params).flags;
	if (!args)
		args = "(null)";
	if (flags & F_ZERO && flags & F_MINUS)
		flags ^= F_ZERO;
	len = ft_strlen(args);
	if (flags & F_PREC)
		len = MIN((*params).precision - (flags & F_PREC), len);
	size = MAX((*params).width, len);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	*(s + size) = 0;
	ft_memset(s, (flags & F_ZERO ? '0' : ' '), size);
	if (flags & F_MINUS)
		ft_strncpy(s, args, len);
	else
		ft_strncpy(s + size - len, args, len);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
