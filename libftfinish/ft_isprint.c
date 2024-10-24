/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:54:31 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/17 14:34:08 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	return (0);
}

// #include "libft.h"
// int	main(void)
// {
// 	int	i = 0;
// 	while (i < 300)
// 	{
// 		printf("%d", ft_isprint(i));
// 		printf("  --->  %d\n", isprint(i));
// 		i++;
// 	}
// }