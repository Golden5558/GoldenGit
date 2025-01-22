/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:32:00 by nberthal          #+#    #+#             */
/*   Updated: 2024/12/18 00:14:34 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_stock(t_list *list)
{
	int	i;

	i = 0;
	while (i < list->len_stock)
	{
		if (list->stock[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*extract_line(t_list *list)
{
	int		len_line;
	int		i;
	char	*line;

	len_line = 0;
	i = 0;
	while (list->stock[len_line] != '\n' && list->stock[len_line] != '\0')
		len_line++;
	if (list->stock[len_line] && list->stock[len_line] == '\n')
		len_line++;
	line = malloc(sizeof(char) * (len_line + 1));
	if (!line)
		return (NULL);
	while (i < len_line)
	{
		line[i] = list->stock[i];
		i++;
	}
	line[i] = '\0';
	free (list->stock);
	return (line);
}

static void	clean_stock(t_list *list, char *remnant)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((list->stock[i] != '\n' && list->stock[i]) && i < list->len_stock)
		i++;
	if (list->stock[i] && list->stock[i] == '\n')
		i++;
	while (i <= list->len_stock)
		remnant[j++] = list->stock[i++];
	remnant[j] = '\0';
}

static int	read_line(int fd, t_list *list)
{
	list->buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!list->buffer)
		return (1);
	list->read_size = read(fd, list->buffer, BUFFER_SIZE);
	if (list->read_size == -1)
		return (free(list->stock), free(list->buffer), 1);
	if (list->read_size == 0)
		return (free(list->buffer), 0);
	while (!check_stock(list) && list->read_size != 0)
	{
		if (list->i == 0)
		{
			list->buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
			if (!list->buffer)
				return (1);
			list->read_size = read(fd, list->buffer, BUFFER_SIZE);
		}
		if (list->read_size == -1)
			return (free(list->stock), free(list->buffer), 1);
		list->i = 0;
		list->buffer[list->read_size] = '\0';
		list->stock = ft_strjoin(list->stock, list->buffer);
		list->len_stock = ft_strlen(list->stock);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	remnant[BUFFER_SIZE + 1];
	t_list		list;

	ft_memset(&list, 0, sizeof(t_list));
	list.stock = ft_strdup("");
	if (!list.stock)
		return (NULL);
	list.i = 1;
	if (*remnant)
	{
		list.stock = ft_substr(remnant, 0, ft_strlen(remnant), list.stock);
		list.len_stock = ft_strlen(list.stock);
		ft_memset(remnant, 0, BUFFER_SIZE + 1);
		if (check_stock(&list))
			return (clean_stock(&list, remnant), extract_line(&list));
	}
	if (read_line(fd, &list) == 1)
		return (NULL);
	if (list.len_stock > 0 && list.read_size == 0)
		return (extract_line(&list));
	else if (list.len_stock == 0 && list.read_size == 0)
		return (free(list.stock), NULL);
	clean_stock(&list, remnant);
	return (extract_line(&list));
}
