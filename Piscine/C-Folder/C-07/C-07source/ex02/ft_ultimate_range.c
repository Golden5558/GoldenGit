/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 00:13:55 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/24 18:27:47 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	r;
	int	i;

	i = 0;
	r = max - min;
	if (min >= max)
	{
		*range = NULL;
		return (0);
	}
	*range = (int *)malloc(sizeof(int) * r);
	if (!(*range))
		return (-1);
	while (min < max)
	{
		(*range)[i] = min;
		i++;
		min++;
	}
	return (r);
}
/*
#include <stdio.h>
int	main(void)
{
	int i = 0;
	int min = 0;
	int max = 3;
	int *tab; 

	printf("taille range :  %d\n", ft_ultimate_range(&tab, min, max));
	if (tab == NULL)
		printf("tab == NULL");
	while(i < max - min)
		printf("%d\n", tab[i++]);
	free(tab);
}*/
