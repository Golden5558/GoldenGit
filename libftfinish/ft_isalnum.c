/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:04:02 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/16 11:49:43 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (c >= 65 && c <= 90)
		return (8);
	if (c >= 97 && c <= 122)
		return (8);
	if (c >= 48 && c <= 57)
		return (8);
	return (0);
}

// #include "libft.h"
// int	main(void)
// {
// 	printf("%d\n", ft_isalnum(65));
// 	printf("%d\n", isalnum(65));
// }