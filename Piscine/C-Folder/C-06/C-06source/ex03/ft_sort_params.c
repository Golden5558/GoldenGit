/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:36:12 by nberthal          #+#    #+#             */
/*   Updated: 2024/09/19 20:17:51 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

void	ft_sort_tab(char **tab, int size)
{
	int		i;
	char	*c;

	while (size >= 0)
	{
		i = 0;
		while (i < size)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				c = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = c;
			}
			i++;
		}
		size--;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	j = 1;
	ft_sort_tab(argv, argc - 1);
	while (j < argc)
	{
		i = 0;
		while (argv[j][i])
		{
			write(1, &argv[j][i], 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
	return (0);
}
