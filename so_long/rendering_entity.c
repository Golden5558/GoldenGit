/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_entity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:01:01 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/13 21:24:15 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	sprite_render_character(void *param)
{
	uint32_t		x;
	uint32_t		y;
	static int		index = 0;
	static double	last_anim;
	t_game			*mlx;

	mlx = (t_game *)param;
	if (mlx_get_time() - last_anim > 0.25)
	{
		index = (index + 1) % 4;
		last_anim = mlx_get_time();
	}
	y = -1;
	while (++y < mlx->chara.img->height)
	{
		x = -1;
		while (++x < mlx->chara.img->width)
		{
			put_pixels_rgba(&mlx->chara, (y * mlx->chara.img->width + x) * 4,
				((y + (index * 100)) * mlx->chara.texture->width + x) * 4);
		}
	}
}

static void	open_door(t_game *game)
{
	int	x;
	int	y;

	x = game->door_close.img->instances->x;
	y = game->door_close.img->instances->y;
	if (game->door_close.img)
		mlx_delete_image(game->mlx, game->door_close.img);
	game->door_open.texture = mlx_load_png("./pictures/door_open.png");
	if (!game->door_open.texture)
		error_terminate_and_exit(game);
	game->door_open.img = mlx_texture_to_image(game->mlx,
			game->door_open.texture);
	if (!game->door_open.img)
		error_terminate_and_exit(game);
	if (mlx_image_to_window(game->mlx, game->door_open.img,
			x, y) == -1)
		error_terminate_and_exit(game);
}

void	put_character(t_game *game)
{
	game->chara.texture = mlx_load_png("./pictures/chara_right.png");
	if (!game->chara.texture)
		error_terminate_and_exit(game);
	game->chara.img = mlx_new_image(game->mlx, 100, 100);
	if (!game->chara.img)
		error_terminate_and_exit(game);
	if (game->map[game->pos.y][game->pos.x] == 'P')
	{
		if (mlx_image_to_window(game->mlx, game->chara.img, (game->pos.x * 100),
				(game->pos.y * 100)) == -1)
			error_terminate_and_exit(game);
		mlx_loop_hook(game->mlx, sprite_render_character, game);
	}
	else if (game->map[game->pos.y][game->pos.x] != 'P')
		error_terminate_and_exit(game);
}

static void	update_position(t_game *game, int y_mov, int x_mov)
{
	if (game->move_count == 2147483647)
	{
		write(1, "Too many movement\n", 18);
		error_terminate_and_exit(game);
	}
	write(1, "Movement count : ", 17);
	ft_putnbr_fd(++game->move_count, 1);
	write(1, "\n", 1);
	game->map[game->pos.y][game->pos.x] = '0';
	game->pos.y += y_mov;
	game->pos.x += x_mov;
	game->map[game->pos.y][game->pos.x] = 'P';
}

int	update_player_position(t_game *game, int y_mov, int x_mov)
{
	if (game->map[game->pos.y + y_mov][game->pos.x + x_mov] == '1'
		|| (game->map[game->pos.y + y_mov][game->pos.x + x_mov] == 'E'
		&& game->pos.c_count != game->pos.collectable))
		return (1);
	if (game->map[game->pos.y + y_mov][game->pos.x + x_mov] == 'E'
		&& game->pos.c_count == game->pos.collectable)
		exit_success(game);
	if (game->map[game->pos.y + y_mov][game->pos.x + x_mov] == 'C')
	{
		update_position(game, y_mov, x_mov);
		game->pos.c_count++;
		if (game->coin.img)
		{
			mlx_delete_image(game->mlx, game->coin.img);
			game->coin.img = NULL;
		}
		if (game->pos.c_count == game->pos.collectable)
			return (open_door(game), 0);
		put_coins(game);
	}
	else
		update_position(game, y_mov, x_mov);
	return (0);
}
