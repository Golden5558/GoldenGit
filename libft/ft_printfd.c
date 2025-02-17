/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 06:08:43 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/17 15:33:59 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_chars(int fd, char arg, va_list ap)
{
	char	*str;

	if (arg == 's')
	{
		str = va_arg(ap, char *);
		if (!str)
			return (write(fd, "(null)", 6));
		ft_putstr_fd(str, fd);
		return (ft_strlen(str));
	}
	else if (arg == 'c')
	{
		ft_putchar_fd(fd, va_arg(ap, int));
		return (1);
	}
	return (0);
}

static int	ft_printarg(int fd, const char *args, va_list ap)
{
	char	format;

	format = args[1];
	if (ft_strchr("diuxXp", format))
		return (ft_print_num(fd, format, ap));
	if (ft_strchr("cs", format))
		return (ft_print_chars(fd, format, ap));
	if (format == '%')
		return (write(fd, "%", 1));
	return (0);
}

int	ft_printfd(int fd, const char *args, ...)
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
			c += ft_printarg(fd, args, ap);
			args += 2;
		}
		else if (*args == '%' && !ft_strchr("cspdiuxX%", *(args + 1)))
			return (-1);
		else
			c += write(fd, args++, 1);
	}
	return (va_end(ap), c);
}
