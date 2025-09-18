/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 00:42:52 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/11 14:13:09 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
char	*ft_strcpy(char *dest, char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (dest);
}
int	main(void)
{
	char source[500] = "tryfdsfdsdfdsffsontdont";
	char goal[500];
	ft_strcpy(goal, source);
	printf("%s", goal);
}
