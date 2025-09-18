/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:38:52 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/19 01:28:35 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_recursive_power(nb, power - 1));
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n", ft_recursive_power(0, 0));
	printf("%d\n", ft_recursive_power(0, -1));
	printf("%d\n", ft_recursive_power(5, 3));
	printf("%d\n", ft_recursive_power(2, 3));
	printf("%d\n", ft_recursive_power(-42, 1));
	printf("%d\n", ft_recursive_power(-42, 2));
	printf("%d\n", ft_recursive_power(-2, 11));
}*/
