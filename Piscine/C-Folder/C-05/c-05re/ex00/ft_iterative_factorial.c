/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 03:45:34 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/18 04:38:56 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	j;

	j = nb - 1;
	if (nb < 0)
		return (0);
	if (nb == 0)
		return (1);
	while (j > 0)
	{
		nb = nb * j;
		j--;
	}
	return (nb);
}
/*
#include <stdio.h>
int	main(void)
{
	int a = 1;
	printf("%d\n", ft_iterative_factorial(a));
}*/
