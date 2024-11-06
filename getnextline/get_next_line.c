/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 06:32:00 by nberthal          #+#    #+#             */
/*   Updated: 2024/11/06 05:35:15 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_end_line(char *stock, int len_stock)
{
	int	i;

	i = 0;
	while (i < len_stock)
	{
		if (stock[i] == '\n' || stock[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

static char	*extract_line(char *stock)
{
	int		len_line;
	int		i;
	char	*line;

	len_line = 0;
	i = 0;
	while (stock[len_line] != '\n' && stock[len_line] != '\0')
		len_line++;
	line = malloc(sizeof(char) * (len_line + 1));
	if (!line)
		return (NULL);
	while (i < len_line)
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	free (stock);
	return (line);
}

static void	clean_stock(char *stock, int len_stock, char *remnant)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((stock[i] != '\n' && stock[i]) && i < len_stock)
		i++;
	i++;
	while (i <= len_stock + 1)
		remnant[j++] = stock[i++];
	remnant[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	remnant[BUFFER_SIZE + 1];
	char		*stock;
	char		*buffer;
	int			check;
	int			len_stock;

	stock = ft_strdup("");
	len_stock = 0;
	if (*remnant)
		stock = ft_substr(remnant, 0, ft_strlen(remnant), stock);
	len_stock += ft_strlen(stock);
	while (!check_end_line(stock, len_stock))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		check = read(fd, buffer, BUFFER_SIZE);
		if (check <= 0)
			return (free(stock), free(buffer), NULL);
		buffer[check] = '\0';
		stock = ft_strjoin(stock, buffer);
		len_stock += check;
	}
	clean_stock(stock, len_stock, remnant);
	return (extract_line(stock));
}
