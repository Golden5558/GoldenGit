/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:25:50 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/24 18:46:47 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*news;

	i = 0;
	if (!s)
		return (NULL);
	news = ft_strdup(s);
	if (!news)
		return (NULL);
	while (news[i])
	{
		news[i] = f(i, s[i]);
		i++;
	}
	return (news);
}
