/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:59:45 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/27 04:22:24 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	verif_dbl(char *base)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (base[len])
		len++;
	while (j < len)
	{
		i = j + 1;
		while (base[i])
		{
			if (base[i] == base[j])
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

static int	ft_verifbase(char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (-1);
		i++;
	}
	if (verif_dbl(base) == 1)
		return (-1);
	if ((*base == '\0') || i == 1)
		return (-1);
	else
		return (i);
}

void	ft_putnbr_base(long long nbr, char *base)
{
	long long	b;

	b = ft_verifbase(base);
	if (b == -1)
		return ;
	if (nbr == -LLONG_MIN)
	{
		write(1, "-", 1);
		ft_putnbr_base(-(nbr / b), base);
		ft_putchar_fd(base[-(nbr % b)], 1);
		return ;
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= b)
		ft_putnbr_base((nbr / b), base);
	ft_putchar_fd(base[nbr % b], 1);
}
