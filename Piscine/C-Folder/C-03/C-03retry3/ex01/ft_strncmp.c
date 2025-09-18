/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 20:00:11 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/17 17:40:26 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	int r;
	unsigned int c = 2;
	char a[] = "ABC";
	char b[] = "AbC";
	r = ft_strncmp(a, a, c);
	printf("%d\n", r);
	r = ft_strncmp(a, b, c);
	printf("%d\n", r);
	r = ft_strncmp(b, a, c);
	printf("%d\n", r);

	printf("Offi : \n\n");

	r = strncmp(a, a, c);
	printf("%d\n", r);
	r = strncmp(a, b, c);
	printf("%d\n", r);
	r = strncmp(b, a, c);
	printf("%d\n", r);
}*/
