/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:18:47 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/18 19:43:34 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	int r;
// 	unsigned int c = 3;
// 	char a[] = "ABC";
// 	char b[] = "AbC";
// 	char d[] = "ABC";

// 	r = ft_memcmp(a, b, c);
// 	printf("ft_memcmp(a, b, %u) = %d\n", c, r);
// 	r = ft_memcmp(a, d, c);
// 	printf("ft_memcmp(a, d, %u) = %d\n", c, r);
// 	r = ft_memcmp(b, d, c);
// 	printf("ft_memcmp(b, d, %u) = %d\n", c, r);

// 	printf("Official memcmp:\n");

// 	r = memcmp(a, b, c);
// 	printf("memcmp(a, b, %u) = %d\n", c, r);
// 	r = memcmp(a, d, c);
// 	printf("memcmp(a, d, %u) = %d\n", c, r);
// 	r = memcmp(b, d, c);
// 	printf("memcmp(b, d, %u) = %d\n", c, r);

// 	return 0;
// }