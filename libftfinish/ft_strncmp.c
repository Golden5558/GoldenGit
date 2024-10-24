/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:35:36 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/17 15:46:02 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	const char *str1 = "Hello";
// 	const char *str2 = "Hello";
// 	const char *str3 = "Hellp";
// 	size_t n = 5;

// 	printf("Comparing '%s' and '%s' with n=%zu\n", str1, str2, n);
// 	printf("ft_strncmp: %d\n", ft_strncmp(str1, str2, n));
// 	printf("strncmp: %d\n", strncmp(str1, str2, n));

// 	printf("Comparing '%s' and '%s' with n=%zu\n", str1, str3, n);
// 	printf("ft_strncmp: %d\n", ft_strncmp(str1, str3, n));
// 	printf("strncmp: %d\n", strncmp(str1, str3, n));

// 	return 0;
// }