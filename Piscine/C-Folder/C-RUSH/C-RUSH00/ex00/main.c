/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugwentzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 14:02:58 by ugwentzi          #+#    #+#             */
/*   Updated: 2024/09/08 13:26:10 by ugwentzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);
void	rush(int x, int y);

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

// check if x && y are valid numbers (between 1 and 255)
int	ft_is_valid(int x, int y)
{
	if (x <= 0 || y <= 0)
	{
		ft_putstr("Error: Please use only positive numbers.\n");
		return (0);
	}
	if (x > 255 || y > 255)
	{
		ft_putstr("Error: Please enter numbers less than 255.\n");
		return (0);
	}
	return (1);
}

int	main(void)
{
	int	x;
	int	y;

	x = 25;
	y = 25;
	if (!ft_is_valid(x, y))
		return (1);
	rush(x, y);
	return (0);
}
