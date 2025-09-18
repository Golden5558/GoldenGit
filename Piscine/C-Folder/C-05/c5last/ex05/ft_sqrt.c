/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:56:28 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/24 16:30:01 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (a <= nb)
	{
		a = i * i;
		if (a == nb)
			return (i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	int r = 0;
	int i = 0;

	printf("%d\n", ft_sqrt(1));
	while (i++ < 10000)
	{
		r = ft_sqrt(i);		
		if (r != 0)
			printf("%d\n", r);
	}

}*/
