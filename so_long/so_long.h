/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:54:34 by nberthal          #+#    #+#             */
/*   Updated: 2025/01/20 23:41:39 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include "./gnl/get_next_line.h"
# include "./lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_img
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;
}	t_img;

typedef struct s_pos
{
	int			x;
	int			y;
	int			end;
	int			start;
	int			collectable;
	int			c_count;
}	t_point;

typedef struct s_game
{
	mlx_t		*mlx;
	char		**map;
	t_img		wall;
	t_img		coin;
	t_img		door_close;
	t_img		door_open;
	t_img		chara;
	t_point		pos;
	int32_t		x_win;
	int32_t		y_win;
	int			move_count;
}	t_game;

// Exits & utils :

void	error_exit(int error);
void	error_terminate_and_exit(t_game *game);
void	exit_success(t_game *game);
void	ft_putnbr_fd(int n, int fd);
void	delete_images_and_textures(t_game *game);

// Rendering :

void	put_pixels_rgba(t_img *image, int i_img, int i_txtr);
void	put_door(t_game *game);
void	put_character(t_game *game);
void	put_walls(t_game *game);
void	put_coins(t_game *game);
int		update_player_position(t_game *game, int y_mov, int x_mov);

// Parsing :

int		str_n(char *str);
void	*ft_freeall(char **tab);
char	**get_map(int line, char *file);
char	**get_map_and_errcheck(char *file, t_point *pos);
int		get_lines_window(char *file);
int		check_path(int x, int y, char **map, t_point *pos);
int		check_map_error(char **map, int line, t_point *pos);
void	get_start_and_check_invalid_char(char **map, t_point *start);

#endif