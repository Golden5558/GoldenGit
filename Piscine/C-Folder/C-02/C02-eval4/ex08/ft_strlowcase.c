/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:26:41 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/11 16:40:51 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strlowcase(char *str)
{
	char	*ret;

	ret = str;
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
			*str += 32;
		str++;
	}
	return (ret);
}
/*
int main(void)
{
	char send[] = "Voici un TEST PoUR PASSeR eN MIn,5343 letrEs";
	char *goal;
	goal = ft_strlowcase(send);
	printf("%s\n", goal);
}*/
