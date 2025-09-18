cc/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dict.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduarte <vduarte@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:31:01 by vduarte           #+#    #+#             */
/*   Updated: 2024/09/22 22:36:26 by vduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	size_dictionnary(char *name)
{
	int		file;
	int		size;
	char	c[1];

	file = open(name, O_RDONLY);
	if (file < 0)
		return (0);
	size = 0;
	while (read(file, c, 1) != 0)
		size ++;
	close (file);
	return (size);
}

char	*make_dictionnary(char *name)
{
	int		file;
	int		size;
	char	*res;

	file = open(name, O_RDONLY);
	if (file < 0)
		return (NULL);
	size = size_dictionnary(name);
	if (size != 0)
	{
		res = malloc(sizeof(char) * size + 1);
		if (!res)
			return (NULL);
		if (read(file, res, size) != size)
			return (NULL);
		res[size + 1] = '\0';
	}
	close (file);
	return (res);
}

int	nb_entry_dictionnary(char *dico)
{
	int	i;
	int	nb_of_entry;

	i = 0;
	nb_of_entry = 0;
	while (dico[i])
	{
		if (dico[i] == '\n')
			nb_of_entry ++;
		i ++;
	}
	return (nb_of_entry);
}
