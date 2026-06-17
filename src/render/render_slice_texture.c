/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_slice_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:07:38 by moodeh            #+#    #+#             */
/*   Updated: 2026/06/17 14:40:14 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// to know what texture u should use u must now where is the texture in pov of the player
// like i know the wall was a side wall
// but how to know it was left or right
// ez use step_x to know
// and for n/s use step_y
// step_y < 0 means y is decreasing -> going UP towards y=0 (NORTH)
// step_y > 0 means y is increasing -> going DOWN away from y=0 (SOUTH)
// int	texture_to_use(t_ray *ray)
// {
// 	if (ray->side == 1)
// 	{
// 		if (ray->step_x > 0) // right
// 			return ((int)EA);
// 		else
// 			return ((int)WE);
// 	}
// 	else
// 	{
// 		if (ray->step_y < 0)
// 			return ((int)NO);
// 		else
// 			return ((int)SO);
// 	}
// }

// here we will start to render a slice by slice
// we start from 0 - WIDTH_OF_SCREEN
// and each slice it depend on
// ray->side     side wall -> 1(left and right texture) | vertical wall
//->0(north and south texture)
// ray_len
// each ray have his own texture to use
// after we choose what texture to use we must know what the hight we use from it
// the closer a wall is , the taller it looks , the further away it is ,
//	the smaller it looks
// ok the len of the ray is the distance between the player and the wall
// and as we know that the relation between the dist and the hight is recessive
// like if the screen is close we have HIGHT is 600 and the ray len is 1.5
// 600/1.5 = 400px as hight of the wall and we start draw it from the middle
// if the wall is 600/6 = 100px len
// if we want to draw we must have 2 points on is up and another one is down
// when we start the drawing we start from up till down
// or as they say start point and end point
// we div on 2 bc we want to start drawing the texture from the middle of the whole window
// and we also div the hight on 2

// 0x00BFFF > blue color
// now for testing i will use static color DONT forget that the ceiling color start from hight 0 on the screen
// till draw_start so we start with ceil coloring
// we make a loop for the whole slice
void	render_a_slice(t_game *game, t_ray *ray, double ray_len, int i_in_width)
{
	//int	texture_type;
	int	hight_of_texture;
	int	draw_start;
	int	draw_end;
	int	i;

	i = 0;
    (void)ray;
	//texture_type = texture_to_use(ray);
	hight_of_texture = (int)(HIGHT_OF_WIN / ray_len);
	draw_start = (-hight_of_texture / 2) + (HIGHT_OF_WIN / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (hight_of_texture / 2) + (HIGHT_OF_WIN / 2);
	if (draw_end >= HIGHT_OF_WIN)
		draw_end = HIGHT_OF_WIN;
	while (i < draw_start)
	{
		put_pixel_to_img_buffer(game->mlx_lib, i_in_width, i,
			game->loaded_texture->c_color);
		i++;
	}
	while (i < draw_end)
	{
		put_pixel_to_img_buffer(game->mlx_lib, i_in_width, i, 0x00BFFF);
		i++;
	}
	while (i < HIGHT_OF_WIN)
	{
		put_pixel_to_img_buffer(game->mlx_lib, i_in_width, i,
			game->loaded_texture->f_color);
		i++;
	}
}
