/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:38:55 by nberthal          #+#    #+#             */
/*   Updated: 2024/11/28 01:32:10 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ar;

	if (nmemb == 0 || size == 0)
	{
		ar = malloc(0);
		if (!ar)
			return (NULL);
		return (ar);
	}
	if (nmemb != (nmemb * size) / size)
		return (NULL);
	ar = (void *)malloc(nmemb * size);
	if (!ar)
		return (NULL);
	ft_memset(ar, 0, nmemb * size);
	return (ar);
}
