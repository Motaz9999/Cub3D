/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_slice_texture_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 22:24:53 by samarnah          #+#    #+#             */
/*   Updated: 2026/07/10 22:26:27 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// to know what texture u should use 
// u must now where is the texture in pov of the player
// like i know the wall was a side wall
// but how to know it was left or right
// ez use step_x to know
// and for n/s use step_y
// step_y < 0 means y is decreasing -> going UP towards y=0 (NORTH)
// step_y > 0 means y is increasing -> going DOWN away from y=0 (SOUTH)
int	texture_to_use_color(t_ray *ray, t_game *game, int tex_x, int tex_y)
{
	if (ray->side == 1)
	{
		if (ray->step_x > 0)
			return (game->loaded_texture->ea_texture[tex_y][tex_x]);
		return (game->loaded_texture->we_texture[tex_y][tex_x]);
	}
	if (ray->step_y < 0)
		return (game->loaded_texture->no_texture[tex_y][tex_x]);
	return (game->loaded_texture->so_texture[tex_y][tex_x]);
}

void	get_draw_limits(double ray_len, int limits[3])
{
	limits[0] = (int)(HIGHT_OF_WIN / ray_len);
	limits[1] = (-limits[0] / 2) + (HIGHT_OF_WIN / 2);
	if (limits[1] < 0)
		limits[1] = 0;
	limits[2] = (limits[0] / 2) + (HIGHT_OF_WIN / 2);
	if (limits[2] >= HIGHT_OF_WIN)
		limits[2] = HIGHT_OF_WIN;
}
