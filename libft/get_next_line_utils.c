/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:35:16 by nberthal          #+#    #+#             */
/*   Updated: 2025/02/18 08:49:34 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new_str);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len, char *b)
{
	char	*new_str;

	new_str = ft_substr(s, start, len);
	free(b);
	return (new_str);
}

void	*ft_free_all(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		free (tab[i++]);
	if (tab)
		free (tab);
	tab = NULL;
	return (NULL);
}
