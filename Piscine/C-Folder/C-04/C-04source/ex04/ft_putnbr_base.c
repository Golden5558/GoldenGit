/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:59:45 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/27 00:42:44 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_verifbase(char *base)
{
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (-1);
		i++;
	}
	j = 1;
	while (base[j])
	{
		if (base[j - 1] == base[j])
			return (-1);
		j++;
	}
	if ((*base == '\0') || i == 1)
		return (-1);	
	else
		return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	b;

	b = 0;
	b = ft_verifbase(base);
	if (b == -1)
		return ;
	if (nbr == -2147483648)
	{
		write(1, "-", 1);
		ft_putnbr_base(-(nbr / b), base);
		ft_putnbr_base(-(nbr % b), base);
	}
	else if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	else if (nbr >= b)
	{
		ft_putnbr_base((nbr / b), base);
		ft_putnbr_base((nbr % b), base);
	}
	else
		ft_putchar(nbr + '0');
}
/*
int	main(void)
{
	ft_putnbr_base(-2147483648, "012345678");
}*/
