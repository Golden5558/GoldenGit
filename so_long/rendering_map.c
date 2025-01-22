/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:52:16 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/14 19:08:12 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_pixels_rgba(t_img *image, int i_img, int i_txtr)
{
	image->img->pixels[i_img + 0] = image->texture->pixels[i_txtr + 0];
	image->img->pixels[i_img + 1] = image->texture->pixels[i_txtr + 1];
	image->img->pixels[i_img + 2] = image->texture->pixels[i_txtr + 2];
	image->img->pixels[i_img + 3] = image->texture->pixels[i_txtr + 3];
}

static void	sprite_render_coin(void *param)
{
	uint32_t		x;
	uint32_t		y;
	static int		index = 0;
	static double	last_anim;
	t_game			*mlx;

	mlx = (t_game *)param;
	if (!mlx->coin.img || !mlx->coin.texture || !mlx->coin.img->pixels)
		return ;
	if (mlx_get_time() - last_anim > 0.1)
	{
		index = (index + 1) % 12;
		last_anim = mlx_get_time();
	}
	y = -1;
	while (++y < mlx->coin.img->height)
	{
		x = -1;
		while (++x < mlx->coin.img->width)
		{
			put_pixels_rgba(&mlx->coin, (y * mlx->coin.img->width + x) * 4,
				((y + (index * 100)) * mlx->coin.texture->width + x) * 4);
		}
	}
}

void	put_coins(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	if (!game->coin.texture)
		game->coin.texture = mlx_load_png("./pictures/coin.png");
	if (!game->coin.texture)
		error_terminate_and_exit(game);
	game->coin.img = mlx_new_image(game->mlx, 100, 100);
	if (!game->coin.img)
		error_terminate_and_exit(game);
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (game->map[y][x] == 'C')
			{
				if (mlx_image_to_window(game->mlx, game->coin.img, (x * 100),
						(y * 100)) == -1)
					error_terminate_and_exit(game);
				mlx_loop_hook(game->mlx, sprite_render_coin, game);
			}
		}
	}
}

void	put_door(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	game->door_close.texture = mlx_load_png("./pictures/door_close.png");
	if (!game->door_close.texture)
		error_terminate_and_exit(game);
	game->door_close.img = mlx_texture_to_image(game->mlx,
			game->door_close.texture);
	if (!game->door_close.img)
		error_terminate_and_exit(game);
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (game->map[y][x] == 'E')
			{
				if (mlx_image_to_window(game->mlx, game->door_close.img,
						(x * 100), (y * 100)) == -1)
					error_terminate_and_exit(game);
			}
		}
	}
}

void	put_walls(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	game->wall.texture = mlx_load_png("./pictures/wall.png");
	if (!game->wall.texture)
		error_terminate_and_exit(game);
	game->wall.img = mlx_texture_to_image(game->mlx, game->wall.texture);
	if (!game->wall.img)
		error_terminate_and_exit(game);
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (game->map[y][x] == '1')
			{
				if (mlx_image_to_window(game->mlx, game->wall.img,
						(x * 100), (y * 100)) == -1)
					error_terminate_and_exit(game);
			}
		}
	}
}
