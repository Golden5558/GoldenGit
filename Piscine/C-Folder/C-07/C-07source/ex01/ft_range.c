/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:27:50 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/24 18:27:18 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*r;
	int	s;
	int	i;

	i = 0;
	s = max - min;
	if (min >= max)
		return (NULL);
	r = malloc(s * sizeof(int));
	if (r == NULL)
		return (NULL);
	while (min < max)
	{
		r[i] = min;
		i++;
		min++;
	}
	return (r);
}
/*
#include <stdio.h>
int	main(void)
{
	int *a;
	int min = 1;
	int max = 9;
	int i = 0;
	a = ft_range(min, max);
	while (i < max - 1)
		printf("%d\n", a[i++]);
	free(a);
}*/
