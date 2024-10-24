/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:24:19 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/22 19:13:04 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	j;
	size_t	i;
	size_t	t;
	size_t	s;

	i = 0;
	j = 0;
	if (!dest && size == 0)
		return (ft_strlen(src));
	i = ft_strlen(src);
	j = ft_strlen(dest);
	if (size <= j)
		return (size + i);
	t = 0;
	s = j;
	while (src[t] && s < size - 1)
		dest[s++] = src[t++];
	dest[s] = '\0';
	return (i + j);
}

// int main(void)
// {
// 	size_t siz = 0;
// 	// char init[] = "Voici le debut";
// 	// // char goal[13] = "de ma phrase.";
// 	// printf("%zu\n", ft_strlcat(NULL, init, siz));
// 	// printf("%s\n",goal);
// 	// char init2[] = "Voici le debut";
// 	char goal2[13] = "de ma phrase.";
// 	printf("%zu\n", strlcat(goal2, NULL, siz));
// 	// printf("%s\n", goal2);
// }
