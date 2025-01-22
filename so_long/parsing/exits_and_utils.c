/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits_and_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:07:41 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/14 18:34:26 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	error_exit(int error)
{
	if (error == 4)
	{
		write(1, "Error : No path valid\n", 22);
		exit(1);
	}
	else if (error == 3)
	{
		write(1, "Error : Map is not a rectangle\n", 31);
		exit(1);
	}
	else if (error == 2)
	{
		write(1, "Error : Size map too big\n", 26);
		exit(1);
	}
	else if (error == 1)
	{
		write(1, "Error : Wrong number of arguments\n", 34);
		exit(1);
	}
	else
	{
		write(1, "Error\n", 6);
		exit(1);
	}
}

void	delete_images_and_textures(t_game *game)
{
	if (game->wall.img)
		mlx_delete_image(game->mlx, game->wall.img);
	if (game->coin.img)
		mlx_delete_image(game->mlx, game->coin.img);
	if (game->door_open.img)
		mlx_delete_image(game->mlx, game->door_open.img);
	if (game->door_close.img)
		mlx_delete_image(game->mlx, game->door_close.img);
	if (game->chara.img)
		mlx_delete_image(game->mlx, game->chara.img);
	if (game->wall.texture)
		mlx_delete_texture(game->wall.texture);
	if (game->coin.texture)
		mlx_delete_texture(game->coin.texture);
	if (game->door_open.texture)
		mlx_delete_texture(game->door_open.texture);
	if (game->door_close.texture)
		mlx_delete_texture(game->door_close.texture);
	if (game->chara.texture)
		mlx_delete_texture(game->chara.texture);
}

void	error_terminate_and_exit(t_game *game)
{
	if (game->map)
		ft_freeall(game->map);
	delete_images_and_textures(game);
	mlx_terminate(game->mlx);
	error_exit(-1);
}

void	exit_success(t_game *game)
{
	if (game->map)
		ft_freeall(game->map);
	delete_images_and_textures(game);
	mlx_terminate(game->mlx);
	write(1, "Game completed ! SUCCESS\n", 25);
	exit(0);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		if (n >= 10)
			ft_putnbr_fd(n / 10, fd);
		c = n % 10 + '0';
		write(fd, &c, 1);
	}
}
