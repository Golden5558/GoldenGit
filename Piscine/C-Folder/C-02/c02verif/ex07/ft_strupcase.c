/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:30:42 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/10 19:24:43 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
*/
char	*ft_strupcase(char *str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}
	return (str);
}
/*
int main(void)
{
	char send[] = "Voici un test pour passer En maj,5343 letrEs";
	char *goal;
	goal = ft_strupcase(send);
	printf("%s\n", send);
}*/
