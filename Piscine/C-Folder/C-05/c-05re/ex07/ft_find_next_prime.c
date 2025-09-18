/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 01:42:54 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/23 20:18:30 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_find_next_prime(int nb)
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
			nb++;
	}
	return (nb);
}
/*
#include <stdio.h>
int main(void)
{
	printf("%d\n", ft_find_next_prime(42));
}*/
