/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:04:56 by moodeh            #+#    #+#             */
/*   Updated: 2026/06/20 10:30:05 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_img(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HIGHT_OF_WIN)
	{
		x = 0;
		while (x < WIDTH_OF_WIN)
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
	render_as_3d(game);
	draw2d_map(game);
	mlx_put_image_to_window(game->mlx_lib->mlx, game->mlx_lib->win,
		game->mlx_lib->img, 0, 0);
	return (0);
}