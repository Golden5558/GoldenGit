/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:16:10 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/16 10:19:21 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char *src)
{
	int	j;

	j = 0;
	while (dest[j])
		j++;
	while (*src)
	{
		dest[j] = *src;
		src++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
/*
#include <stdio.h>

int main(void)
{
	char goal[] = "Voici une phrase";
	char source[] = "dans une phrase";
	char *end;
	end = ft_strcat(goal, source);
	printf("%s\n", end);
}*/
