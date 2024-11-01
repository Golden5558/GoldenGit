/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:08:43 by nberthal          #+#    #+#             */
/*   Updated: 2024/11/01 15:14:16 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_percent(int *e)
{
	char	a;

	a = '%';
	*e = write(1, &a, 1);
	if (*e == -1)
		return (-1);
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

static int	ft_printarg(const char *args, va_list ap, int *e)
{
	int	c;

	c = 0;
	if (*args == '%' && *(args + 1) == 'c')
		c += ft_print_char(ap, e);
	if (*args == '%' && *(args + 1) == 's')
		c += ft_print_str(ap, e);
	if (*args == '%' && *(args + 1) == 'p')
		c += ft_print_memory(ap, e);
	if (*args == '%' && *(args + 1) == 'd')
		c += ft_print_decimal(ap, e);
	if (*args == '%' && *(args + 1) == 'i')
		c += ft_print_decimal(ap, e);
	if (*args == '%' && *(args + 1) == 'u')
		c += ft_print_unsigned_decimal(ap, e);
	if (*args == '%' && *(args + 1) == 'x')
		c += ft_print_hexa(args, ap, e);
	if (*args == '%' && *(args + 1) == 'X')
		c += ft_print_hexa(args, ap, e);
	if (*args == '%' && *(args + 1) == '%')
		c += ft_print_percent(e);
	return (c);
}

static int	ft_process_arg(const char *args, va_list ap, int *c)
{
	int	e;

	e = 0;
	while (*args)
	{
		if (ft_isarg(args))
		{
			*c += ft_printarg(args, ap, &e);
			if (e == -1)
				return (-1);
			args += 2;
		}
		else
		{
			if (*args == '%' && !ft_isarg(args))
				return (-1);
			e = write(1, args++, 1);
			if (e == -1)
				return (-1);
			*c += 1;
		}
	}
	return (0);
}

int	ft_printf(const char *args, ...)
{
	va_list	ap;
	int		e;
	int		c;

	c = 0;
	e = 0;
	if (!args)
		return (-1);
	va_start(ap, args);
	if (ft_process_arg(args, ap, &c) == -1)
		return (va_end(ap), -1);
	return (va_end(ap), c);
}
