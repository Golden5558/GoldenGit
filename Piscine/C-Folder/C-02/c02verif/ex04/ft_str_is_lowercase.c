/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:35:07 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/10 16:45:22 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
int	ft_str_is_lower_case(char *str)
{
	while (*str)
	{
		if (!(*str >= 'a' && *str <= 'z'))
			return (0);
		str++;
	}
	return (1);
}
/*
int main(void)
{
    char jsp[] = "xjsdkzjzjxckjcnn";
    char jsp2[] = "d654fdf fdfsdf";
    char jsp3[] = ""; 
    int res;
    res = ft_str_is_lower_case(jsp);
    printf("%d\n", res);    
    res = ft_str_is_lower_case(jsp2);
    printf("%d\n", res);    
    res = ft_str_is_lower_case(jsp3);
    printf("%d\n", res);    
}*/
