/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 01:59:45 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/27 00:49:57 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	verif_dbl(char *base)
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

int	ft_verifbase(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (-1);
		i++;
	}
	j = 1;
	if (verif_dbl(base) == 1)
		return (-1);
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

int	main(void)
{
	ft_putnbr_base(546654, "0123456789abcdef");
}
