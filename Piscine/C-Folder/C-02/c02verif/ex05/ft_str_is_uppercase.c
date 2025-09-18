/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:38:31 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/10 17:42:22 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
int	ft_str_is_uppercase(char *str)
{
	while (*str)
	{
		if (!(*str >= 'A' && *str <= 'Z'))
			return (0);
		str++;
	}
	return (1);
}
/*
int main(void)
{
    char jsp[] = "RFLSDKFLSDKJFLKS";
    char jsp2[] = "d654fdf fdfsdf";
    char jsp3[] = ""; 
    int res;
    res = ft_str_is_uppercase(jsp);
    printf("%d\n", res);    
    res = ft_str_is_uppercase(jsp2);
    printf("%d\n", res);    
    res = ft_str_is_uppercase(jsp3);
    printf("%d\n", res);    
}*/
