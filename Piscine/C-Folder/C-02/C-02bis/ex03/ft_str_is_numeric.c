/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:22:47 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/11 09:53:09 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
int	ft_str_is_numeric(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}
/*
int main(void)
{
	int res;
	char jsp[] = "54543651";
	char jsp1[] = "545t3651";
	char jsp2[] = "";
	res = ft_str_is_numeric(jsp);
	printf("%d\n", res);
	res = ft_str_is_numeric(jsp1);
	printf("%d\n", res);
	res = ft_str_is_numeric(jsp2);
	printf("%d\n", res);
}*/
