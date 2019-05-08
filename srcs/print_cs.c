/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:49:39 by smorty            #+#    #+#             */
/*   Updated: 2019/05/07 19:32:31 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(const char argc, t_frmt *params)
{
	char	*s;
	int		printed;
	int		size;

	if ((*params).zero && (*params).minus)
		(*params).zero = 0;
	size = ((*params).width > 0 ? (*params).width : 1);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	*(s + size) = 0;
	ft_memset(s, ((*params).zero ? '0' : ' '), size);
	if ((*params).minus)
		*s = argc;
	else
		*(s + size - 1) = argc;
	printed = write(1, s, size);
	free(s);
	return (printed);
}

int	print_string(const char *args, t_frmt *params)
{
	char	*s;
	int		printed;
	int		size;
	int		len;

	if (!args)
		return (write(1, "(null)", 6));
	if ((*params).zero && ((*params).minus || (*params).precision >= 0))
		(*params).zero = 0;
	len = ft_strlen(args);
	if ((*params).precision >= 0)
		len = ((*params).precision > len ? len : (*params).precision);
	size = ((*params).width > len ? (*params).width : len);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	*(s + size) = 0;
	ft_memset(s, ((*params).zero ? '0' : ' '), size);
	if ((*params).minus)
		s = ft_strncpy(s, args, len);
	else
		while (len)
		{
			*(s + size - len) = *args;
			args++;
			len--;
		}
	printed = write(1, s, size);
	free(s);
	return (printed);
}
