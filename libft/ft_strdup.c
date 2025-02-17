/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:54:07 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/24 15:38:24 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s1;
	size_t	i;

	i = ft_strlen(s) + 1;
	s1 = (char *)malloc(sizeof(char) * i);
	if (!s1)
		return (NULL);
	ft_strlcpy(s1, s, i);
	return (s1);
}
