/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:15:47 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/30 21:17:33 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_print_char(va_list ap, int *e)
{
	char	c;

	c = (char)va_arg(ap, int);
	*e = write(1, &c, 1);
	if (*e == -1)
		return (-1);
	return (1);
}

int	ft_print_str(va_list ap, int *e)
{
	char	*str;
	int		len;

	str = va_arg(ap, char *);
	if (!str)
		return (*e = write(1, "(null)", 6), *e);
	len = ft_strlen(str);
	while (*str)
	{
		*e = write(1, str++, 1);
		if (*e == -1)
			return (-1);
	}
	return (len);
}
