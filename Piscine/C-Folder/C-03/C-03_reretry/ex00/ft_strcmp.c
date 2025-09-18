/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:19:50 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/17 17:39:20 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1++ || *s2++)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int c;
	char a[] = "";
	char b[] = "";

	c = ft_strcmp(a, a);
	printf("%d\n", c);
	c = ft_strcmp(b, a);
	printf("%d\n", c);
	c = ft_strcmp(a, b);

	printf("%d\n\n", c);
	printf("strcmp offi :\n");

	c = strcmp(a, a);
	printf("%d\n", c);
	c = strcmp(b, a);
	printf("%d\n", c);
	c = strcmp(a, b);
	printf("%d\n\n", c);

	printf("strcmp offi direct :\n");

	
	printf("%d\n", strcmp(a, a));
	printf("%d\n", strcmp(b, a));
	printf("%d\n", strcmp(a, b));
}*/
