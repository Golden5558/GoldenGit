/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:51:15 by nberthal          #+#    #+#             */
/*   Updated: 2024/12/18 15:31:36 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	get_start_and_collectables(char **map, t_point *start)
{
	int		x;
	int		y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				start->x = x;
				start->y = y;
			}
			x++;
		}
		y++;
	}
}

void	*ft_freeall(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free (tab[i++]);
	free (tab);
	return (NULL);
}

static char	**copy_map(char **map, int line)
{
	char	**cpy_map;
	char	**start_cpy_map;
	int		index;
	int		len;

	len = str_n(map[0]);
	cpy_map = malloc(sizeof(char *) * (line + 1));
	if (!cpy_map)
		return (NULL);
	start_cpy_map = cpy_map;
	while (*map)
	{
		index = -1;
		*cpy_map = malloc(sizeof(char) * (len + 1));
		if (!cpy_map)
			return (ft_freeall(cpy_map), NULL);
		while ((*map)[++index])
			(*cpy_map)[index] = (*map)[index];
		(*cpy_map)[index] = '\0';
		map++;
		cpy_map++;
	}
	*cpy_map = NULL;
	return (start_cpy_map);
}

int	check_path(int x, int y, char **map, t_point *pos)
{
	if (map[y][x] == 'C')
		pos->c_count += 1;
	if (map[y][x] == 'E')
	{
		if (pos->c_count == pos->collectable)
			return (1);
		else
			return (0);
	}
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (0);
	if (map[y][x] != '0' && map[y][x] != 'C' && map[y][x] != 'P')
		return (0);
	map[y][x] = 'F';
	if (check_path(x + 1, y, map, pos))
		return (1);
	if (check_path(x - 1, y, map, pos))
		return (1);
	if (check_path(x, y + 1, map, pos))
		return (1);
	if (check_path(x, y - 1, map, pos))
		return (1);
	return (0);
}

char	**get_map_and_errcheck(char *file, t_point *pos_s)
{
	char	**map;
	char	**verif_map;
	int		line;

	line = get_lines_window(file);
	map = get_map(line, file);
	if (!map)
		error_exit(1);
	get_start_and_collectables(map, pos_s);
	pos_s->c_count = 0;
	if (check_map_error(map, line, pos_s) == -1)
	{
		ft_freeall(map);
		error_exit(1);
	}
	verif_map = copy_map(map, line);
	if (check_path(pos_s->x, pos_s->y, verif_map, pos_s) == 0)
	{
		ft_freeall(verif_map);
		ft_freeall(map);
		error_exit(1);
	}
	ft_freeall(verif_map);
	return (map);
}
