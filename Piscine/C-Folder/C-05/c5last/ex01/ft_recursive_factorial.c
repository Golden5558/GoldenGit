/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:22:11 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/18 15:46:10 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_factorial(int nb)
{
	if (nb == 0)
		return (1);
	if (nb < 0)
		return (0);
	else
		return (nb *= ft_recursive_factorial(nb -1));
}
/*
#include <stdio.h>
int	main(void)
{
	int i = -2;
	printf("Factorial -1 ---> 12\n\n");
	while (++i < 13)
		printf("nb ==> %d\n", ft_recursive_factorial(i));
}*/
