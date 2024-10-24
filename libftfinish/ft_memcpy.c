/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:16:38 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/18 18:01:04 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*src1;
	unsigned char		*dest1;
	size_t				i;

	if (dest == 0 && src == 0)
		return (NULL);
	src1 = (const unsigned char *)src;
	dest1 = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}

// int	main(void)
// {
	// char src[] = "voici une string";
	// char dest[50];
	// char src1[] = "voici une string";
	// char dest1[50];
	// size_t i = 8;
	// ft_memcpy(dest, src, i);
	// memcpy(dest1, src1, i);
	// printf("Mon memcpy : %s\n", dest);
	// 	printf("Le memcpy : %s\n", dest1);
	// ft_memcpy(((void*)0), ((void*)0), 3);
	// memcpy(((void*)0), ((void*)0), 3);
// }