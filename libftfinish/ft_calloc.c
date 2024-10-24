/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:38:55 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/24 04:22:55 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ar;

	if (nmemb > 0 && size > 0 && nmemb > 2147483647 / size)
		return (NULL);
	ar = (char *)malloc(nmemb * size);
	if (!ar)
		return (NULL);
	ft_memset(ar, 0, nmemb * size);
	return (ar);
}
// int	main(void)
// {
// 	size_t	nmemb = 5;
// 	size_t	size = 2;

// 	unsigned char	*ar;
// 	ar = ft_calloc(nmemb, size);
// 	size_t i = 0;
// 	while (i < nmemb)
// 		write(1, &ar[i++], size);
// 	printf("%p", ar);
// 	free (ar);
// 
	// unsigned char	*ar1;
	// ar1 = calloc(nmemb, size);
	// size_t j = 0;
	// while (j < nmemb)
	// 	write(1, &ar1[j++], size);
	// printf("%p", ar1);
	// free (ar1);
// }
