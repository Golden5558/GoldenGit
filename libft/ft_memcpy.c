/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:16:38 by nberthal          #+#    #+#             */
/*   Updated: 2024/11/28 01:34:46 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*src1;
	unsigned char		*dest1;
	size_t				i;

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
