/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:20:07 by nberthal          #+#    #+#             */
/*   Updated: 2024/11/01 14:44:44 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_getdec(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while ((n / 10) != 0)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

static int	ft_putchar(int c)
{
	int	a;

	a = write(1, &c, 1);
	return (a);
}

void	ft_putnbr_fd(int n, int *e)
{
	if (n == -2147483648)
	{
		*e = write(1, "-2147483648", 11);
		if (*e == -1)
			return ;
	}
	else if (n < 0)
	{
		*e = write(1, "-", 1);
		if (*e == -1)
			return ;
		n = -n;
		ft_putnbr_fd(n, e);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, e);
		ft_putnbr_fd(n % 10, e);
	}
	else
	{
		*e = ft_putchar(n + '0');
		if (*e == -1)
			return ;
	}
}

int	ft_print_decimal(va_list ap, int *e)
{
	int	num;

	num = va_arg(ap, int);
	ft_putnbr_fd(num, e);
	if (num < 0)
		return (ft_getdec(num) + 1);
	else
		return (ft_getdec(num));
}
