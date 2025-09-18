/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:48:55 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/22 01:41:48 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int	i;
	int	temp;

	i = 1;
	temp = nb;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (i < power)
	{
		nb = temp * nb;
		i++;
	}
	return (nb);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_iterative_power(0, 0));
	printf("%d\n", ft_iterative_power(0, -1));
	printf("%d\n", ft_iterative_power(5, 3));
	printf("%d\n", ft_iterative_power(2, 3));
	printf("%d\n", ft_iterative_power(-42, 0));
	printf("%d\n", ft_iterative_power(-42, 1));
	printf("%d\n", ft_iterative_power(-42, 2));
	printf("%d\n", ft_iterative_power(-2, 11));
}*/
