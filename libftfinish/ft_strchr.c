/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:04:27 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/18 18:21:47 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s1;

	s1 = (char *)s;
	while (*s1)
	{
		if (*s1 == (unsigned char)c)
			return (s1);
		s1++;
	}
	if (*s1 == (unsigned char)c)
		return (s1);
	return (NULL);
}

// int	main(void)
// {
// 	const char s[] = "je cherche A";

// 	printf("%p\n", ft_strchr(s, 'e'));
// 	printf("%p\n", strchr(s, 'e'));
// 	printf("%p\n", ft_strchr("teste", 357));
// 	printf("%p\n", ft_strchr("teste", 1024));
// 	printf("%p\n", strchr("teste", 357));
// 	printf("%p\n", strchr("teste", 1024));
// }