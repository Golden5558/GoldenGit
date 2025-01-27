/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:08:43 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/26 10:23:18 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_num(char arg, va_list ap)
{
	int	c;
	int	num;

	c = 0;
	if (ft_strchr("di", arg))
	{
		num = va_arg(ap, int);
		ft_putnbr_base((long)num, "0123456789");
		return (ft_getdec(num, 10));
	}
	else if (arg == 'u' || arg == 'x' || arg == 'X' || arg == 'p')
		return (ft_print_hex_uint(arg, ap));
	return (0);
}

static int	ft_print_chars(char arg, va_list ap)
{
	char	*str;

	if (arg == 's')
	{
		str = va_arg(ap, char *);
		if (!str)
			return (write(1, "(null)", 6));
		ft_putstr_fd(str, 1);
		return (ft_strlen(str));
	}
	else if (arg == 'c')
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		return (1);
	}
	return (0);
}

static int	ft_printarg(const char *args, va_list ap)
{
	char	format;

	format = args[1];
	if (ft_strchr("diuxXp", format))
		return (ft_print_num(format, ap));
	if (ft_strchr("cs", format))
		return (ft_print_chars(format, ap));
	if (format == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *args, ...)
{
	va_list	ap;
	int		c;

	c = 0;
	if (!args)
		return (-1);
	va_start(ap, args);
	while (*args)
	{
		if (*args == '%' && ft_strchr("cspdiuxX%", *(args + 1)))
		{
			c += ft_printarg(args, ap);
			args += 2;
		}
		else if (*args == '%' && !ft_strchr("cspdiuxX%", *(args + 1)))
			return (-1);
		else
			c += write(1, args++, 1);
	}
	return (va_end(ap), c);
}
