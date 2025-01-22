/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:50:04 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/21 01:30:52 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_character(t_game *game, int y_move, int x_move)
{
	static double	last_press = 0;

	if ((mlx_get_time() - last_press > 0.2)
		&& !update_player_position(game, y_move / 100, x_move / 100))
	{
		game->chara.img->instances->y += y_move;
		if (x_move == 100)
		{
			if (game->chara.texture)
				mlx_delete_texture(game->chara.texture);
			game->chara.texture = mlx_load_png("./pictures/chara_right.png");
			if (!game->chara.texture)
				error_terminate_and_exit(game);
		}
		if (x_move == -100)
		{
			if (game->chara.texture)
				mlx_delete_texture(game->chara.texture);
			game->chara.texture = mlx_load_png("./pictures/chara_left.png");
			if (!game->chara.texture)
				error_terminate_and_exit(game);
		}
		game->chara.img->instances->x += x_move;
		last_press = mlx_get_time();
	}
}

static void	keys_hook(void *param)
{
	t_game			*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE) == true)
	{
		if (game->map)
			ft_freeall(game->map);
		delete_images_and_textures(game);
		mlx_terminate(game->mlx);
		exit (0);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP) == true)
		move_character(game, -100, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN) == true)
		move_character(game, 100, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) == true)
		move_character(game, 0, 100);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) == true)
		move_character(game, 0, -100);
}

static void	open_window(t_game *game, char *file)
{
	game->map = get_map_and_errcheck(file, &game->pos);
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
		error_terminate_and_exit(game);
}

static void	close_callback(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->map)
		ft_freeall(game->map);
	delete_images_and_textures(game);
	mlx_terminate(game->mlx);
	write(1, "Exit : Closing so_long\n", 22);
	exit(0);
}

int32_t	main(int argc, char **argv)
{
	t_game	game;
	int		len_argv;

	if (argc != 2)
		error_exit(1);
	len_argv = ft_strlen(argv[1]);
	if (len_argv < 4 || argv[1][len_argv - 1] != 'r' && argv[1][len_argv - 2]
		!= 'e' && argv[1][len_argv - 3] != 'b' && argv[1][len_argv - 4] != '.')
	{
		write(1, "Error : Wrong extension\n", 23);
		exit(1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	open_window(&game, argv[1]);
	put_walls(&game);
	put_coins(&game);
	put_character(&game);
	put_door(&game);
	mlx_loop_hook(game.mlx, keys_hook, &game);
	mlx_close_hook(game.mlx, close_callback, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
