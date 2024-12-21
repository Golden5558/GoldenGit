/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:54:34 by nberthal          #+#    #+#             */
/*   Updated: 2024/12/19 21:05:24 by nberthal         ###   ########.fr       */
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

# define wall_s	100

typedef struct	s_img {
	mlx_image_t		*img;
	mlx_texture_t	*mlx_t;
}	t_img;

typedef struct	s_pos {
	int			x;
	int			y;
	int			end;
	int			start;
	int			collectable;
	int			c_count;
}	t_point;

typedef struct	s_game {
	mlx_t		*mlx;
	char		**map;
	t_img		wall;
	t_img		coin;
	t_img		door;
	t_img		character;
	t_point		*pos;
	int32_t		x_win;
	int32_t		y_win;
}	t_game;


void	error_exit(int error);
void	error_terminate_and_exit(t_game *game, int error);
void	sprite_render_idle(void *param);
void	*ft_freeall(char **tab);
char	**get_map(int line, char *file);
char	**get_map_and_errcheck(char *file, t_point *pos_s);
int		get_lines_window(char *file);
int		str_n(char *str);
int		check_path(int x, int y, char **map, t_point *pos);
int		check_map_error(char **map, int line, t_point *pos);
void	get_start_and_collectables(char **map, t_point *pos_s);

#endif