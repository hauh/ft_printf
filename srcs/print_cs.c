/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorty <smorty@student.21school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:49:39 by smorty            #+#    #+#             */
/*   Updated: 2019/05/08 17:57:46 by smorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(const char argc, t_frmt *params)
{
	char	*s;
	int		printed;
	int		size;

	if ((*params).zero && (*params).minus)
		(*params).zero = 0;
	size = MAX((*params).width, 1);
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

int	print_s(const char *args, t_frmt *params)
{
	char	*s;
	int		printed;
	int		size;
	int		len;

	if (!args)
		return (write(1, "(null)", 6));
	if ((*params).zero && ((*params).minus || (*params).flag_prec))
		(*params).zero = 0;
	len = ft_strlen(args);
	if ((*params).flag_prec)
		len = MIN((*params).precision - (*params).flag_prec, len);
	size = MAX((*params).width, len);
	if (!(s = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	*(s + size) = 0;
	ft_memset(s, ((*params).zero ? '0' : ' '), size);
	if ((*params).minus)
		ft_strncpy(s, args, len);
	else
		ft_strncpy(s + size - len, args, len);
	printed = write(1, s, size);
	free(s);
	return (printed);
}
