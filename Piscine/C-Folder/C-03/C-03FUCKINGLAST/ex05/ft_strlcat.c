/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 23:26:30 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/17 00:22:33 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	j;
	unsigned int	i;
	unsigned int	t;
	unsigned int	s;

	i = 0;
	j = 0;
	while (src[i])
		i++;
	while (dest[j])
		j++;
	if (size <= j)
		return (size + i);
	t = 0;
	s = j;
	while (src[t] && s < size - 1)
		dest[s++] = src[t++];
	dest[s] = '\0';
	return (i + j);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int main(void)
{
	unsigned int siz = 20;
	char init[] = "Voici le debut";
	char goal[300] = "de ma phrase.";
	char init2[] = "Voici le debut";
	char goal2[300] = "de ma phrase.";
//	unsigned int ret;
//	ret = ft_strlcpy(goal, init, siz );
	printf("%d\n", ft_strlcat(goal, init, siz));
	printf("%s\n",goal);
//	ret = strlcpy(goal2, init2, siz );
	printf("%zu\n", strlcat(goal2, init2, siz));
	printf("%s\n", goal2);
}*/
