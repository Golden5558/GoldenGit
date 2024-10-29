/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:21:20 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/29 00:10:02 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putnbr_hexa(unsigned int nbr, char *base, int *count)
{
	if (nbr >= 16)
	{
		ft_putnbr_hexa((nbr / 16), base, count);
		ft_putnbr_hexa((nbr % 16), base, count);
	}
	else
	{
		ft_putchar_fd(base[nbr], 1);
		*count += 1;
	}
}

static void	ft_putnbr_hexalong(unsigned long nbr, char *base, int *count)
{
	if (nbr >= 16)
	{
		ft_putnbr_hexalong((nbr / 16), base, count);
		ft_putnbr_hexalong((nbr % 16), base, count);
	}
	else
	{
		ft_putchar_fd(base[nbr], 1);
		*count += 1;
	}
}

int	ft_print_hexa(const char *args, va_list ap)
{
	int				c;

	c = 0;
	if (*args == '%' && *(args + 1) == 'x')
		ft_putnbr_hexa(va_arg(ap, unsigned int), "0123456789abcdef", &c);
	if (*args == '%' && *(args + 1) == 'X')
		ft_putnbr_hexa(va_arg(ap, unsigned int), "0123456789ABCDEF", &c);
	return (c);
}

int	ft_print_memory(va_list ap)
{
	int				c;
	unsigned long	a;

	c = 2;
	a = va_arg(ap, unsigned long);
	if (a == 0)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	ft_putnbr_hexalong(a, "0123456789abcdef", &c);
	return (c);
}
