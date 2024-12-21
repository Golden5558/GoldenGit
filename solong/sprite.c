/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberthal <nberthal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:52:16 by nberthal          #+#    #+#             */
/*   Updated: 2024/12/19 23:55:51 by nberthal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	sprite_render_idle(void *param)
// {
// 	static int32_t	i_sprite = 0;
// 	int32_t			x;
// 	int32_t			y;
// 	int32_t			i_img;
// 	int32_t			i_txtr;
// 	t_game 			*mlx;
// 	double			current_time;
	
// 	mlx = (t_game *)param;
// 	mlx->mlx->delta_time = mlx_get_time();
// 	y = 0;
// 	mlx->idle.texture.height = 320;
// 	mlx->idle.texture.width = 64;
// 	current_time = mlx_get_time();
// 	if (current_time - mlx->mlx->delta_time <= 1.0)
// 	{
// 		mlx->mlx->delta_time = current_time;
// 		if (i_sprite > 3)
// 			i_sprite = 0;
// 		else
// 			i_sprite++;
// 		while (y < mlx->idle.texture.height / 4 + (i_sprite * 80))
// 		{
// 			x = 0;
// 			while (x < mlx->idle.texture.width)
// 			{
// 				i_img = (y * mlx->idle.image.width + x) * 4;
// 				i_txtr = ((y + i_sprite * 80) * mlx->idle.texture.width + x) * 4;
// 				mlx->idle.image.img->pixels[i_img] = mlx->idle.texture.txtr->pixels[i_txtr];
// 				x++;
// 			}
// 			y++;
// 		}
// 	}
// }

#include "so_long.h"

// void	sprite_render_idle(void *param)
// {
// 	static int32_t	i_sprite = 0;
// 	int32_t			x;
// 	int32_t			y;
// 	int32_t			i_img;
// 	int32_t			i_txtr;
// 	t_game 			*mlx;
// 	double			current_time;
	
// 	// Define sprite dimensions
// 	const int sprite_height = 80;
// 	const int sprite_width = 64;
	
// 	mlx = (t_game *)param;
// 	current_time = mlx_get_time();
	
// 	// Corrected time condition to trigger every 1 second
// 	if (current_time - mlx->mlx->delta_time >= 1.0)
// 	{
// 		mlx->mlx->delta_time = current_time; // Update delta_time
		
// 		// Cycle through sprite frames
// 		if (i_sprite > 3)
// 			i_sprite = 0;
// 		else
// 			i_sprite++;
		
// 		y = 0;
// 		while (y < sprite_height && y < mlx->idle.image.height)
// 		{
// 			x = 0;
// 			while (x < sprite_width && x < mlx->idle.image.width)
// 			{
// 				// Calculate image and texture indices
// 				i_img = (y * mlx->idle.image.width + x) * 4;
// 				i_txtr = ((y + i_sprite * sprite_height) * mlx->idle.texture.width + x) * 4;
				
// 				// Boundary checks to prevent out-of-bounds access
// 				if (i_img >= 0 && i_img < (mlx->idle.image.width * mlx->idle.image.height * 4) &&
// 				    i_txtr >= 0 && i_txtr < (mlx->idle.texture.width * mlx->idle.texture.height * 4))
// 				{
// 					// Copy pixel data (assuming RGBA; adjust if necessary)
// 					mlx->idle.image.img->pixels[i_img]     = mlx->idle.texture.txtr->pixels[i_txtr];     // Red
// 					mlx->idle.image.img->pixels[i_img + 1] = mlx->idle.texture.txtr->pixels[i_txtr + 1]; // Green
// 					mlx->idle.image.img->pixels[i_img + 2] = mlx->idle.texture.txtr->pixels[i_txtr + 2]; // Blue
// 					mlx->idle.image.img->pixels[i_img + 3] = mlx->idle.texture.txtr->pixels[i_txtr + 3]; // Alpha
// 				}
// 				else
// 				{
// 					// Optional: Log an error or handle the out-of-bounds case
// 				}
				
// 				x++;
// 			}
// 			y++;
// 		}
// 	}
// }
