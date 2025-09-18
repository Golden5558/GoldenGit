/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:48:04 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/10 16:21:19 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
int	ft_str_is_alpha(char *str)
{
	while (*str)
	{
		if (!((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z')))
			return (0);
		str++;
	}
	return (1);
}
/*
int	main(void)
{
	char jsp[] = "JemiappelleHenry";
	char jsp2[] = "dtsdfdf fdfsdf";
	char jsp3[] = "";
	int res;
	res = ft_str_is_alpha(jsp);
	printf("%d\n", res);	
	res = ft_str_is_alpha(jsp2);
	printf("%d\n", res);	
	res = ft_str_is_alpha(jsp3);
	printf("%d\n", res);	
}*/
