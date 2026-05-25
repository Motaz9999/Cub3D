/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:04:56 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/25 20:52:06 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_img(t_game *game)
{
	int	x;
	int	y;
	int	screen_width;
	int	screen_height;

	screen_width = game->config_file_data->map_data->map_width * BLOCK;
	screen_height = game->config_file_data->map_data->map_hight * BLOCK;
	y = 0;
	while (y < screen_height)
	{
		x = 0;
		while (x < screen_width)
		{
			put_pixel_to_img_buffer(game->mlx_lib, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

int	render(void *game_void)
{
	t_game *game;

	game = (t_game *)game_void;
	handle_movement(game);

	clear_img(game);
	draw2d_map(game);

	mlx_put_image_to_window(game->mlx_lib->mlx, game->mlx_lib->win,
		game->mlx_lib->img, 0, 0);
	return (0);
}