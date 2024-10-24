/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:54:07 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/17 14:15:42 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s1;
	size_t	i;

	i = ft_strlen(s) + 1;
	s1 = (char *)malloc(sizeof(char) * i);
	if (!s1)
		return (NULL);
	ft_strlcpy(s1, s, i);
	return (s1);
}

// int	main(void)
// {
// 	const char	*str = "Hello, World!";
// 	char		*dup1;
// 	char		*dup2;

// 	dup1 = ft_strdup(str);
// 	dup2 = strdup(str);

// 	if (dup1 && dup2)
// 	{
// 		printf("Original string: %s\n", str);
// 		printf("ft_strdup: %s\n", dup1);
// 		printf("strdup: %s\n", dup2);
// 	}
// 	else
// 	{
// 		printf("Memory allocation failed\n");
// 	}

// 	free(dup1);
// 	free(dup2);

// 	return (0);
// }