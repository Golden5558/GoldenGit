/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:25:50 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/22 02:41:52 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	jensairien(unsigned int i, char c)
// {
// 	(void)i;
// 	if (c >= 'A' && c <= 'Z')
// 		c += 32;
// 	return (c);
// }

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

// int	main(void)
// {
// 	printf("%s\n", ft_strmapi("VOICI UNE STRING", jensairien));
// }