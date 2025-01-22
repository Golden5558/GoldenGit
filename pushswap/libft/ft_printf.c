/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:08:43 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/15 23:37:52 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getdec(int n, int base)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while ((n / base) != 0)
	{
		n = n / base;
		i++;
	}
	return (i + 1);
}

static int	ft_print_num(char arg, va_list ap)
{
	int			c;
	long long	num;

	num = va_arg(ap, long long);
	c = 0;
	if (ft_strchr("idu", arg))
	{
		ft_putnbr_base(num, "0123456789");
		return (c = ft_getdec(num, 10), c);
	}
	else if (arg == 'p')
	{
		if (num == 0)
			return (c = write(1, "(nil)", 5), c);
		c += write(1, "0x", 2);
		ft_putnbr_base(num, "0123456789abcdef");
	}
	else if (arg == 'x')
		ft_putnbr_base(num, "0123456789abcdef");
	else if (arg == 'X')
		ft_putnbr_base(num, "0123456789ABCDEF");
	return (c += ft_getdec(num, 16), c);
}

static int	ft_print_chars(char arg, va_list ap)
{
	int		c;
	char	*str;

	c = 0;
	if (arg == 's')
	{
		str = va_arg(ap, char *);
		ft_putstr_fd(str, 1);
		c = ft_strlen(str);
	}
	else if (arg == 'c')
	{
		(void)str;
		ft_putchar_fd(va_arg(ap, int), 1);
		c = 1;
	}
	return (c);
}

static int	ft_printarg(const char *args, va_list ap)
{
	int	c;

	c = 0;
	if (ft_strchr("idu", *(args + 1)))
		c += ft_print_num(*(args + 1), ap);
	else if (ft_strchr("xXp", *(args + 1)))
		c += ft_print_num(*(args + 1), ap);
	else if (ft_strchr("cs", *(args + 1)))
		c += ft_print_chars(*(args + 1), ap);
	else if (*args + 1 == '%')
		c += write(1, "%", 1);
	return (c);
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
