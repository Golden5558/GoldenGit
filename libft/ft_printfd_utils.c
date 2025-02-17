/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:14:38 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/17 15:31:25 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_ptr(int fd, void *ptr)
{
	unsigned long	num;
	int				c;

	c = 0;
	num = (unsigned long)ptr;
	if (num == 0)
		return (write(fd, "(nil)", 5));
	c += write(fd, "0x", 2);
	ft_putnbr_base_fd(num, "0123456789abcdef", fd);
	return (c + ft_getdec(num, 16));
}

static int	ft_print_hex_uint(int fd, char arg, va_list ap)
{
	unsigned int	num;

	if (arg == 'u')
	{
		num = va_arg(ap, unsigned int);
		ft_putnbr_base_fd((unsigned long)num, "0123456789", fd);
		return (ft_getdec(num, 10));
	}
	if (arg == 'p')
		return (ft_print_ptr(fd, va_arg(ap, void *)));
	num = va_arg(ap, unsigned int);
	if (arg == 'x')
		ft_putnbr_base_fd((unsigned long)num, "0123456789abcdef", fd);
	if (arg == 'X')
		ft_putnbr_base_fd((unsigned long)num, "0123456789ABCDEF", fd);
	return (ft_getdec(num, 16));
}

int	ft_print_num(int fd, char arg, va_list ap)
{
	int	c;
	int	num;

	c = 0;
	if (ft_strchr("di", arg))
	{
		num = va_arg(ap, int);
		if (num < 0)
		{
			ft_putchar_fd(fd, '-');
			c++;
			ft_putnbr_base_fd((long)(-num), "0123456789", fd);
			return (c + ft_getdec(-num, 10));
		}
		else
		{
			ft_putnbr_base_fd((long)num, "0123456789", fd);
			return (ft_getdec(num, 10));
		}
	}
	else if (arg == 'u' || arg == 'x' || arg == 'X' || arg == 'p')
		return (ft_print_hex_uint(fd, arg, ap));
	return (0);
}
