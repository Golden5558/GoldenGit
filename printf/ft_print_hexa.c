/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:21:20 by nberthal          #+#    #+#             */
/*   Updated: 2024/11/01 14:43:53 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnb_hexa(unsigned int nb, char *base, int *count, int *e)
{
	int	p;

	if (nb >= 16)
	{
		ft_putnb_hexa((nb / 16), base, count, e);
		ft_putnb_hexa((nb % 16), base, count, e);
	}
	else
	{
		p = base[nb];
		*e = write(1, &p, 1);
		if (*e == -1)
			return ;
		*count += 1;
	}
}

static void	ft_putnb_hexalong(unsigned long nb, char *base, int *count, int *e)
{
	int	p;

	if (nb >= 16)
	{
		ft_putnb_hexalong((nb / 16), base, count, e);
		ft_putnb_hexalong((nb % 16), base, count, e);
	}
	else
	{
		p = base[nb];
		*e = write(1, &p, 1);
		if (*e == -1)
			return ;
		*count += 1;
	}
}

int	ft_print_hexa(const char *args, va_list ap, int *e)
{
	int				c;

	c = 0;
	if (*args == '%' && *(args + 1) == 'x')
	{
		ft_putnb_hexa(va_arg(ap, unsigned int), "0123456789abcdef", &c, e);
		if (*e == -1)
			return (-1);
	}
	if (*args == '%' && *(args + 1) == 'X')
	{
		ft_putnb_hexa(va_arg(ap, unsigned int), "0123456789ABCDEF", &c, e);
		if (*e == -1)
			return (-1);
	}
	return (c);
}

int	ft_print_memory(va_list ap, int *e)
{
	int				c;
	unsigned long	a;

	c = 2;
	a = va_arg(ap, unsigned long);
	if (a == 0)
		return (*e = write(1, "(nil)", 5), *e);
	*e = write(1, "0x", 2);
	if (*e == -1)
		return (-1);
	ft_putnb_hexalong(a, "0123456789abcdef", &c, e);
	if (*e == -1)
		return (-1);
	return (c);
}
