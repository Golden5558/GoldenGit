/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 01:01:43 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/23 20:18:15 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb)
{
	int	i;
	int	a;

	i = 0;
	a = nb;
	if (nb <= 0 || nb == 1)
		return(0);
	while (--a > 1)
	{
		i = nb % a;
		if (i == 0)
			return (0);
	}
	return (1);
}
/*
#include <stdio.h>
int	main(void)
{
	int i = -2;
	printf("Test %d\n", ft_is_prime(-2));
	printf("Test %d\n", ft_is_prime(0));
	printf("Test %d\n", ft_is_prime(1));
	while (i++ < 12)
	{
		if (ft_is_prime(i) == 1)
			printf("Nombres premiers %d\n", i);
	}
}*/
