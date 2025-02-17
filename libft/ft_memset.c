/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:16:27 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/24 15:35:26 by nberthal         ###   ########.fr       */
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
