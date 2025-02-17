/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:14:38 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/11 01:28:56 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_ptr(void *ptr)
{
	unsigned long	num;
	int				c;

	c = 0;
	num = (unsigned long)ptr;
	if (num == 0)
		return (write(1, "(nil)", 5));
	c += write(1, "0x", 2);
	ft_putnbr_base(num, "0123456789abcdef");
	return (c + ft_getdec(num, 16));
}

static int	ft_print_hex_uint(char arg, va_list ap)
{
	unsigned int	num;

	if (arg == 'u')
	{
		num = va_arg(ap, unsigned int);
		ft_putnbr_base((unsigned long)num, "0123456789");
		return (ft_getdec(num, 10));
	}
	if (arg == 'p')
		return (ft_print_ptr(va_arg(ap, void *)));
	num = va_arg(ap, unsigned int);
	if (arg == 'x')
		ft_putnbr_base((unsigned long)num, "0123456789abcdef");
	if (arg == 'X')
		ft_putnbr_base((unsigned long)num, "0123456789ABCDEF");
	return (ft_getdec(num, 16));
}

int	ft_print_num(char arg, va_list ap)
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
