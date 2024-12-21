/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_positions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:07:41 by nberthal          #+#    #+#             */
/*   Updated: 2024/12/20 00:40:10 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	error_exit(int error)
{
	if (error == 2)
	{
		write(1, "Error : Size map too big\n", 26);
		exit(1);
	}
	else
	{
		write(1, "Error\n", 6);
		exit(1);
	}
}

void	error_terminate_and_exit(t_game *game, int error)
{
	if (game->map)
		ft_freeall(game->map);
	if (error == 1)
		mlx_terminate(game->mlx);
	error_exit(1);
}

// int	main(int argc, char **argv)
// {
// 	char	**map;
// 	t_point	pos_s;
// 	int		i;

// 	i = 0;
// 	if (argc != 2)
// 	{
// 		write(1, "Error\n", 6);
// 		return (1);
// 	}
// 	map = get_map_and_errcheck(argv[1], &pos_s);
// 	printf("%d, %d\n", pos_s.x, pos_s.y);
// 	while (map[i])
// 	{
// 		printf("%s\n", map[i++]);
// 	}
// 	printf("%s\n", map[i]);
// 	ft_freeall(map);
// }
