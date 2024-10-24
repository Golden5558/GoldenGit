/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:47:35 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/18 19:40:49 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
		while (n-- > 0)
			((unsigned char *)dest)[n] = ((const unsigned char *)src)[n];
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

// int	main(void)
// {
// 	char src[] = "voici une string";
// 	char src1[] = "voici une string";
// 	size_t i = 4;
// 	char dest[50];
// 	char dest1[50];

// 	// Test 1: Overlapping regions
// 	printf("Test 1: Overlapping regions\n");
// 	ft_memmove(&src[5], src, i);
// 	memmove(&src1[5], src1, i);
// 	printf("mon memmove : %s\n", src);
// 	printf("the memmove : %s\n", src1);

// 	// Test 2: Non-overlapping regions
// 	printf("\nTest 2: Non-overlapping regions\n");
// 	ft_memmove(dest, src, i);
// 	memmove(dest1, src1, i);
// 	printf("mon memmove : %s\n", dest);
// 	printf("the memmove : %s\n", dest1);

// 	// Test 3: Entire string
// 	printf("\nTest 3: Entire string\n");
// 	ft_memmove(dest, src, strlen(src) + 1);
// 	memmove(dest1, src1, strlen(src1) + 1);
// 	printf("mon memmove : %s\n", dest);
// 	printf("the memmove : %s\n", dest1);

// 	return 0;
// }
// int	main(void)
// {
// 	char *src = NULL;
// 	char *dest = NULL;
// 	size_t n = 5;

// 	// Test 1: Both src and dest are NULL
// 	printf("Test 1: Both src and dest are NULL\n");
// 	printf("mon memmove : %p\n", ft_memmove(dest, src, n));
// 	printf("the memmove : %p\n", memmove(dest, src, n));

// 	// Test 2: src is NULL
// 	dest = malloc(n);
// 	printf("\nTest 2: src is NULL\n");
// 	printf("mon memmove : %p\n", ft_memmove(dest, src, n));
// 	printf("the memmove : %p\n", memmove(dest, src, n));
// 	free(dest);

// 	// Test 3: dest is NULL
// 	src = malloc(n);
// 	printf("\nTest 3: dest is NULL\n");
// 	printf("mon memmove : %p\n", ft_memmove(dest, src, n));
// 	printf("the memmove : %p\n", memmove(dest, src, n));
// 	free(src);

// 	return 0;
// }