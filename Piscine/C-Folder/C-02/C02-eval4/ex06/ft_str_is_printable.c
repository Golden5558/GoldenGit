/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:46:06 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/10 18:28:07 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
int	ft_str_is_printable(char *str)
{
	while (*str)
	{
		if (!(*str >= 32 && *str <= 126))
			return (0);
		str++;
	}
	return (1);
}
/*
int main(void)
{
    char jsp[] = "dsf6sd452@#$#$%S";
    char jsp2[] = "dssdfsdf¶¶¶¶¶";
    char jsp3[] = ""; 
    int res;
    res = ft_str_is_printable(jsp);
    printf("%d\n", res);    
    res = ft_str_is_printable(jsp2);
    printf("%d\n", res);    
    res = ft_str_is_printable(jsp3);
    printf("%d\n", res);    
}*/
