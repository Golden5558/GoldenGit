/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:50:04 by nberthal          #+#    #+#             */
/*   Updated: 2024/12/20 18:41:03 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_close(void *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE) == true)
	{
		mlx_terminate(mlx);
		exit (0);
	}
}

static int	open_window(t_game *game, char *file)
{
	game->map = get_map_and_errcheck(file, game->pos);
	game->x_win = str_n(game->map[0]) * 100;
	game->y_win = 0;
	while (game->map[game->y_win])
		game->y_win++;
	game->y_win *= 100;
	if (game->x_win > 3800 || game->y_win > 2000)
	{
		ft_freeall(game->map);
		error_exit(2);
	}
	game->mlx = mlx_init(game->x_win, game->y_win, "So_long", false);
	if (!game->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (0);
}

static void	put_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->wall.mlx_t = mlx_load_png("./pictures/wall.png");
	if (!game->wall.mlx_t)
		error_terminate_and_exit(game, 1);
	game->wall.img = mlx_texture_to_image(game->mlx, game->wall.mlx_t);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
				// printf("%c", game->map[y][x]);
				if (game->map[y][x] == '1')
				{
					if (mlx_image_to_window(game->mlx, game->wall.img, (x * wall_s), (y * wall_s)) == -1)
						error_terminate_and_exit(game, 1);
				}
				x++;
		}
		y++;
	}  // mlx_delete_image()
}

int32_t	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit(1);
	if (open_window(&game, argv[1]))
		return (EXIT_FAILURE);
	put_walls(&game);
	// game.character.mlx_t = mlx_load_png("./pictures/idle_spritesheet.png");
	// if (!game.character.mlx_t)
	// 	return (EXIT_FAILURE);
	// game.character.img = mlx_new_image(game.mlx, 64, 80);
	// if (mlx_image_to_window(game.mlx, game.character.img, 64, 80) == -1)
	// {
	// 	mlx_close_window(game.mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return (EXIT_FAILURE);
	// }
	// mlx_loop_hook(game.mlx, sprite_render_idle, &game);
	mlx_loop_hook(game.mlx, check_close, game.mlx);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
