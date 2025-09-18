/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:00:58 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/24 18:20:46 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

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

char	*ft_fill(char *dest, char *sep, char **strs, int size)
{
	int	i;

	i = 0;
	*dest = '\0';
	while (i < size)
	{
		ft_strcat(dest, strs[i++]);
		if (i < size)
			ft_strcat(dest, sep);
	}
	return (dest);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*dest;
	int		length;
	int		i;

	i = 0;
	length = 0;
	if (size == 0)
	{
		dest = malloc(sizeof(char));
		if (!dest)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	while (i < size)
		length += ft_strlen(strs[i++]);
	dest = malloc(sizeof(char) * length + 1 + (ft_strlen(sep) * size - 1));
	if (!dest)
		return (NULL);
	return (ft_fill(dest, sep, strs, size));
}
/*
#include <stdio.h>
int	main(void)
{
	int size = 5;
	char *sep = ", ";
	char *strs[5];
	strs[0] = "test1";	
	strs[1] = "test2";	
	strs[2] = "test3";	
	strs[3] = "test4";	
	strs[4] = "test5";
	char *dest = ft_strjoin(size, strs, sep);
	printf("%s\n", dest);
	free(dest);
}*/
