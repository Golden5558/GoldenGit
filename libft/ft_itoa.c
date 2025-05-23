/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nerthal <nerthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:42:22 by nerthal          #+#    #+#             */
/*   Updated: 2024/10/19 16:20:58 by nerthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_getstr(char *s, long n)
{
	if (n >= 10)
	{
		ft_getstr(s - 1, n / 10);
		ft_getstr(s, n % 10);
	}
	else
		*s = (n % 10) + '0';
}

int	ft_getdec(unsigned long long n, int base)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while ((n / base) != 0)
	{
		n = n / base;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		dec;
	long	nlong;

	nlong = (long)n;
	dec = ft_getdec(n, 10);
	if (n < 0)
		dec++;
	s = malloc(sizeof(char) * (dec + 1));
	if (!s)
		return (NULL);
	s[dec] = '\0';
	if (nlong < 0)
	{
		s[0] = '-';
		nlong = -nlong;
	}
	ft_getstr(s + dec - 1, nlong);
	return (s);
}
