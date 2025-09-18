/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:33:48 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/10 23:23:18 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putmin(char *str)
{
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
			*str += 32;
		str++;
	}
}

char	*ft_strcapitalize(char *str)
{
	int	i;

	i = 0;
	ft_putmin(str);
	str[i] -= 32;
	while (str[i])
	{
		if (!(str[i] < 'a' || str[i] > 'z'))
		{
			if ((str[i - 1] < 'a' || str[i - 1] > 'z')
				&& (str[i - 1] < '0' || str[i - 1] > '9')
				&& !(str[i - 1] > 'A' && str[i - 1] < 'Z'))
			{
				str[i] -= 32;
			}
			i++;
		}
		else
			i++;
	}
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char test[] = "salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un";
	printf("%s\n", ft_strcapitalize(test));
}*/
