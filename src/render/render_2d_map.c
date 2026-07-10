/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 20:45:28 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/10 22:10:49 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_block(t_game *game, int pos[2], int color, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel_to_img_buffer(game->mlx_lib,
				pos[0] + i, pos[1] + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_walls(t_game *game)
{
	int	i;
	int	j;
	int	pos[2];

	i = 0;
	while (i < game->config_file_data->map_data->map_hight)
	{
		j = 0;
		while (j < game->config_file_data->map_data->map_width)
		{
			if (game->config_file_data->map_data->map[i][j] == '1')
			{
				pos[0] = j * BLOCK;
				pos[1] = i * BLOCK;
				draw_block(game, pos,
					game->loaded_texture->c_color, BLOCK);
			}
			j++;
		}
		i++;
	}
}

static void	draw_map_background(t_game *game)
{
	int	x;
	int	y;
	int	map_width;
	int	map_height;

	map_width = (game->config_file_data->map_data->map_width - 1)
		* BLOCK;
	map_height = game->config_file_data->map_data->map_hight * BLOCK;
	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			put_pixel_to_img_buffer(game->mlx_lib, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	draw2d_map(t_game *game)
{
	int	full_size;
	int	half_size;
	int	pos[2];

	full_size = (int)(HITBOX * 2 * BLOCK);
	half_size = full_size / 2;
	pos[0] = (int)(game->player->x * BLOCK) - half_size;
	pos[1] = (int)(game->player->y * BLOCK) - half_size;
	draw_map_background(game);
	draw_walls(game);
	draw_block(game, pos, 0xFF0000, full_size);
}
