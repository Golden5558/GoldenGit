/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:37:11 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/18 21:45:40 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *str)
{
	int	minus;
	int	a;
	int	i;

	a = 0;
	i = 1;
	minus = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus++;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
		a = a * 10 + (*str++ - 48);
	if (minus % 2 == 1)
		a = -a;
	return (a);
}
/*
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char test[] = "    ++6542sasd221";
	printf("%d\n", ft_atoi(test));
	printf("%d\n", atoi(test));
}*/
