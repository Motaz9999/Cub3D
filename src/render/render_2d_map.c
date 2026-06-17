/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:45:28 by moodeh            #+#    #+#             */
/*   Updated: 2026/06/17 14:13:22 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	draw_block(int x, int y, int color, int size, t_game *game)
// {
// 	for (int i = 0; i < size; i++)
// 	{
// 		for (int j = 0; j < size; j++)
// 		{
// 			put_pixel_to_img_buffer(game->mlx_lib, x + i, y + j, color);
// 		}
// 	}
// }

// static void	draw_walls(t_game *game)
// {
// 	for (int i = 0; i < game->config_file_data->map_data->map_hight; i++)
// 	{
// 		for (int j = 0; j < game->config_file_data->map_data->map_width; j++)
// 		{
// 			if (game->config_file_data->map_data->map[i][j] == '1')
// 			{
// 				draw_block(j * BLOCK, i * BLOCK, game->loaded_texture->c_color,
// 					BLOCK, game);
// 			}
// 		}
// 	}
// }
// void draw_lines();

// // here we find the full size from blocksize -> wall
// // and from the hitbox->its for the player
// // then multiply it with 2 then make int now i have the full size as 2d
// // then div by 2 so i can draw it form center to center
// // then after draw_walls i draw player
// void	draw2d_map(t_game *game)
// {
// 	int full_size = (int)(HITBOX * 2 * BLOCK);

// 	int half_size = full_size / 2;

// 	int start_x = (int)(game->player->x * BLOCK) - half_size;
// 	int start_y = (int)(game->player->y * BLOCK) - half_size;

// 	draw_walls(game);

// 	draw_block(start_x, start_y, 0xFF0000, full_size, game);
//     draw_lines(start_x , start_y , 0xFF0000 , game);
// }