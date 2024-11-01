/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_decimal.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:20:35 by nberthal          #+#    #+#             */
/*   Updated: 2024/11/01 14:43:10 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_unsigned(unsigned int n, int *e, int *dec)
{
	int	tmp;

	if (n >= 10)
	{
		ft_putnbr_unsigned(n / 10, e, dec);
		ft_putnbr_unsigned(n % 10, e, dec);
	}
	else
	{
		tmp = n + '0';
		*e = write(1, &tmp, 1);
		if (*e == -1)
			return ;
		*dec += 1;
	}
}

int	ft_print_unsigned_decimal(va_list ap, int *e)
{
	unsigned int	num;
	int				dec;

	dec = 0;
	num = va_arg(ap, unsigned int);
	ft_putnbr_unsigned(num, e, &dec);
	if (*e == -1)
		return (-1);
	return (dec);
}
