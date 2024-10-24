/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:49:26 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/17 15:31:46 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (size < 1)
		return (j);
	while (i < (size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

// int	main(void)
// {
// 	size_t	i = 8;
// 	char dst[50];
// 	char dst1[50];
// 	char src[] = "The phrase source";
// 	ft_strlcpy(dst, src, i);
// 	strlcpy(dst1, src, i);
// 	printf("%s    %zu\n", dst, i);
// 	printf("%s    %zu\n", dst1, i);
// }