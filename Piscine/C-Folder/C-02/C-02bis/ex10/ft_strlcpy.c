/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 00:26:07 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/11 17:32:35 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	int				j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (size < 1)
		return (j);
	while (src[i] && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (j);
}

#include <stdio.h>

int main(void)
{
	char ini[] = "Voici un phrase source";
	unsigned int siz = 0;
	char goal[0];
	unsigned int ret;

	ret = ft_strlcpy(goal, ini, siz);
	printf("%s\n%d\n", goal, ret);
}
