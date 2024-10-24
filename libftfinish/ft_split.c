/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 01:23:36 by nberthal          #+#    #+#             */
/*   Updated: 2024/10/24 04:18:25 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t		i;
	const char	*s1;

	i = 0;
	while (*s)
	{
		s1 = s + 1;
		if (*s != c && *s1 == c)
			i++;
		if (*s1 == '\0' && *s != c && c != '\0')
			i++;
		s++;
	}
	return (i);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*s1;
	size_t	i;

	i = n + 1;
	s1 = (char *)malloc(sizeof(char) * i);
	if (!s1)
		return (NULL);
	i = 0;
	while (i < n)
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

static size_t	ft_getendword(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	*ft_freeall(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free (tab[i++]);
	free (tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	j;
	size_t	words;

	j = 0;
	if (!s)
		return (NULL);
	words = ft_countword(s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (j < words)
		{
			tab[j++] = ft_strndup(s, ft_getendword(s, c));
			if (!tab[j - 1])
				return (ft_freeall(tab));
		}
		while (*s != c && *s)
			s++;
	}
	return (tab[j] = NULL, tab);
}

// int	main(void)
// {
// 	char	**result;
// 	char	s[] = "      split       this for   me  !       ";
// 	char	c = ' ';
// 	size_t	i;

// 	result = ft_split(s, c);
// 	i = 0;
// 	while (i < ft_countword(s, c) + 1)
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);
// }
// 	result = ft_split("  Cb de mots a cette phrase", ' ');
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);

// 	result = ft_split("    Cb de mots a cette phrase      ", ' ');
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("%s\n", result[i]);
// 		free(result[i]);
// 		i++;
// 	}
// 	free(result);

// 	return (0);
// }