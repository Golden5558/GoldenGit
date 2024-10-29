/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:08:43 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/29 03:18:55 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_char(va_list ap)
{
	char	c;

	c = (char)va_arg(ap, int);
	write(1, &c, 1);
	return (1);
}

static int	ft_print_percent(va_list pa)
{
	char	a;

	(void)pa;
	a = '%';
	write(1, &a, 1);
	return (1);
}

static int	ft_isarg(const char *args)
{
	if (*args == '%' && *(args + 1) == 'c')
		return (1);
	if (*args == '%' && *(args + 1) == 's')
		return (1);
	if (*args == '%' && *(args + 1) == 'p')
		return (1);
	if (*args == '%' && *(args + 1) == 'd')
		return (1);
	if (*args == '%' && *(args + 1) == 'i')
		return (1);
	if (*args == '%' && *(args + 1) == 'u')
		return (1);
	if (*args == '%' && *(args + 1) == 'x')
		return (1);
	if (*args == '%' && *(args + 1) == 'X')
		return (1);
	if (*args == '%' && *(args + 1) == '%')
		return (1);
	else
		return (0);
}

static int	ft_printarg(const char *args, va_list ap)
{
	int	c;

	c = 0;
	if (*args == '%' && *(args + 1) == 'c')
		c += ft_print_char(ap);
	if (*args == '%' && *(args + 1) == 's')
		c += ft_print_str(ap);
	if (*args == '%' && *(args + 1) == 'p')
		c += ft_print_memory(ap);
	if (*args == '%' && *(args + 1) == 'd')
		c += ft_print_decimal(ap);
	if (*args == '%' && *(args + 1) == 'i')
		c += ft_print_decimal(ap);
	if (*args == '%' && *(args + 1) == 'u')
		c += ft_print_unsigned_decimal(ap);
	if (*args == '%' && *(args + 1) == 'x')
		c += ft_print_hexa(args, ap);
	if (*args == '%' && *(args + 1) == 'X')
		c += ft_print_hexa(args, ap);
	if (*args == '%' && *(args + 1) == '%')
		c += ft_print_percent(ap);
	return (c);
}

int	ft_printf(const char *args, ...)
{
	va_list	ap;
	int		c;

	c = 0;
	va_start(ap, args);
	while (*args)
	{
		if (ft_isarg(args))
		{
			c += ft_printarg(args, ap);
			args += 2;
		}
		else
		{
			write(1, args++, 1);
			c++;
		}
	}
	va_end(ap);
	return (c);
}
