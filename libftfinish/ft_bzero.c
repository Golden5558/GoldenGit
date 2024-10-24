/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:21:17 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/17 11:25:39 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s1;
	size_t			i;

	i = 0;
	s1 = (unsigned char *)s;
	while (i < n)
		s1[i++] = 0;
}

// int	main(void)
// {
// 	char str[] = "voic une string";
// 	int i = 0;
// 	int n = 6;
// 	ft_bzero(str, n);
// 	while (i <= 15)
// 		write(1, &str[i++], 1);
// 	i = 0;
// 	bzero(str, n);
// 	while (i <= 15)
// 		write(1, &str[i++], 1);
// }