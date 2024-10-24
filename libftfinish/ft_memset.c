/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:16:27 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/16 11:48:55 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	d;
	size_t			i;

	d = (unsigned char)c;
	i = 0;
	s1 = s;
	while (i < n)
		s1[i++] = d;
	return (s);
}

// int	main(void)
// {
// 	char str[] = "voic une string";
// 	ft_memset(str, '4', 6);
// 	printf("%s\n", str);
// }