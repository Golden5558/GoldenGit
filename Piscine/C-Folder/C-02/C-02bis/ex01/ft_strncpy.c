/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:39:51 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/10 15:45:37 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}
/*
#include <stdio.h>
#include <unistd.h>
int	main(void)
{
	int max = 60;
	char source[] = "Nouvelle phrase !!";
	char goal[60] = "Voici le but a jspuauoidire !";
	char *result;
	result = ft_strncpy(goal, source, max);
//	printf("%s\n", result);
	int i =0;
	while (i < max)
		write(1 , &result[i++], 1);
}*/
