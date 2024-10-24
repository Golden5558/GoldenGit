/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:57:36 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/22 19:11:36 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	compare;
	char	*big1;

	i = 0;
	big1 = (char *)big;
	compare = 1;
	if (!big && len == 0)
		return (NULL);
	if (*little == '\0')
		return (big1);
	while (big1[i] && i < len)
	{
		if ((big1[i] == *little) && (i + ft_strlen(little) <= len))
			compare = ft_memcmp(&big1[i], little, ft_strlen(little));
		if (compare == 0)
			return (&big1[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	// const char big[] = "Hello, this is a simple string";
// 	const char little[] = "this";
// 	size_t len = 0;
// 	// char *result_ft;
// 	char *result_std;
// 	// result_ft = ft_strnstr(NULL, little, len);
// 	result_std = strnstr(NULL, little, len);
// 	// printf("%s\n", result_ft);
// 	// printf("%p\n", result_ft);
// 	printf("%s\n", result_std);
// 	printf("%p\n", result_std);
// 	return (0);
// }

// int	main(void)
// {
// 	const char *big = "Hello, this is a simple string";
// 	// const char *little = "this";
// 	size_t len = 0;
// 	// char *result_ft;
// 	char *result_std;

// 	// // Test case 1: both strings are non-NULL
// 	// result_ft = ft_strnstr(big, little, len);
// 	// result_std = strnstr(big, little, len);
// 	// printf("Test case 1:\n");
// 	// printf("ft_strnstr: %s\n", result_ft);
// 	// printf("strnstr: %s\n", result_std);

// 	// Test case 2: big is NULL
// 	// result_ft = ft_strnstr(NULL, little, len);
// 	// printf("ft_strnstr: %p\n", result_ft);
// 	// result_std = strnstr(NULL, little, len);
// 	// printf("strnstr: %p\n", result_std);

// 	// // Test case 3: little is NULL
// 	// result_ft = ft_strnstr(big, NULL, len);
// 	result_std = strnstr(big, NULL, len);
// 	// printf("Test case 3:\n");
// 	// printf("ft_strnstr: %p\n", result_ft);
// 	printf("strnstr: %p\n", result_std);

// 	// // Test case 4: both strings are NULL
// 	// result_ft = ft_strnstr(NULL, NULL, len);
// 	// result_std = strnstr(NULL, NULL, len);
// 	// printf("Test case 4:\n");
// 	// printf("ft_strnstr: %p\n", result_ft);
// 	// printf("strnstr: %p\n", result_std);

// 	return (0);
// }