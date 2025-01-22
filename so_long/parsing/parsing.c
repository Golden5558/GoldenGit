/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:42:16 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/20 23:42:04 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	str_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\n' && str[i])
		i++;
	return (i);
}

int	get_lines_window(char *file)
{
	int		fd;
	int		line;
	int		check_read;
	char	*buffer;

	line = 0;
	fd = open(file, O_RDONLY);
	buffer = malloc(sizeof(char) * 1);
	if (!buffer)
		return (-1);
	check_read = read(fd, buffer, 1);
	if (check_read <= 0)
		return (-1);
	while (buffer && check_read > 0)
	{
		check_read = read(fd, buffer, 1);
		if (check_read < 0)
			return (-1);
		if (buffer[0] == '\n')
			line++;
	}
	close(fd);
	free(buffer);
	return (line + 1);
}

char	**get_map(int line, char *file)
{
	int		fd;
	int		i;
	char	**map;

	if (line == -1)
		return (NULL);
	i = 0;
	fd = open(file, O_RDONLY);
	map = malloc(sizeof(char *) * (line + 1));
	if (!map)
		return (NULL);
	while (i < line - 1)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
			return (ft_freeall(map));
		map[i][str_n(map[i])] = '\0';
		i++;
	}
	map[i] = get_next_line(fd);
	if (!map[i])
		return (ft_freeall(map));
	map[++i] = NULL;
	close(fd);
	return (map);
}

static int	check_map(char **map, t_point *pos)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'E')
				pos->end++;
			if (map[y][x] == 'P')
			{
				pos->x = x;
				pos->y = y;
				pos->start++;
			}
			if (map[y][x++] == 'C')
				pos->collectable++;
		}
	}
	return (pos->end != 1 || pos->start != 1 || pos->collectable < 1);
}

int	check_map_error(char **map, int line, t_point *pos)
{
	int	index;

	index = 0;
	if (check_map(map, pos) == 1)
		return (-1);
	while (map[0][index])
	{
		if (map[0][index++] != '1')
			return (-1);
	}
	index = 0;
	while (map[line - 1][index])
	{
		if (map[line - 1][index++] != '1')
			return (-1);
	}
	index = ft_strlen(*map) - 1;
	while (*map)
	{
		if ((*map)[0] != '1' || (size_t)index != ft_strlen(*map) - 1
			|| (*map)[index] != '1')
			return (-1);
		map++;
	}
	return (0);
}
