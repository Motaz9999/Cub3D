/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_slice_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:07:38 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/10 23:52:26 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// here we will start to render a slice by slice
// we start from 0 - WIDTH_OF_SCREEN
// and each slice it depend on
// ray->side     side wall -> 1(left and right texture) | vertical wall
//->0(north and south texture)
// ray_len
// each ray have his own texture to use
// after we choose what texture to use
// we must know what the hight we use from it
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
// we div on 2 bc we want to start drawing the texture
// 		from the middle of the whole window
// and we also div the hight on 2
// 0x00BFFF > blue color
// now for testing i will use static color
//		DONT forget that the ceiling color start from hight 0 on the screen
// till draw_start so we start with ceil coloring
// we make a loop for the whole slice
// after testing and seeing all things work fine
//		now we continue with texture not color
// so every texture size is 64x64 so its easy to put them together
// not that easy bc u need to know which column to take from the texture
// and secound which texture to use
// 	if (ray->side == 1) hit vertical wall
// 	else //hit horizontal wall
//  after knowing which wall being hit
//		we want to know how many of the wall being hit
// double precentage = exact_hit - floor(exact_hit);
// its for knowing exactly where it hit the wall
// like if i have a wall number 5 and the ray hit 5.6
//		so hit 60% of the way down that block.
// Flip texture if looking South or West so it's not mirrored
// tex_x = (int)(precentage * TEXTURE);
// we must draw the pixels from 60% of the way across the texture image = 38.4
// so we take col number 38 (the whole col)
// if (ray->side == 1 && ray_dir_x < 0)
//		tex_x = TEXTURE - tex_x - 1;
// the tex_x have 64 pixel in total widths
// imagin we the height of texture is 300 pixel
// 		and the my are is 64 pixel how can i draw it?
// stretch it like in array we moving 1 by 1
// 		now i will be moving TEXTURE/hight_of_texture each time
// 64/300 =0.213
// ceiling

static int	get_texture_x(t_game *game, t_ray *ray, double ray_data[3])
{
	double	exact_hit;
	double	percentage;
	int		tex_x;

	if (ray->side == 1)
		exact_hit = game->player->y + ray_data[0] * ray_data[2];
	else
		exact_hit = game->player->x + ray_data[0] * ray_data[1];
	percentage = exact_hit - floor(exact_hit);
	tex_x = (int)(percentage * TEXTURE);
	tex_x = TEXTURE - tex_x - 1;
	if (ray->side == 1 && ray_data[1] < 0)
		tex_x = TEXTURE - tex_x - 1;
	return (tex_x);
}

static void	draw_ceiling(t_game *game, int column, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel_to_img_buffer(game->mlx_lib, column, y,
			game->loaded_texture->c_color);
		y++;
	}
}

static int	draw_wall(t_game *game, t_ray *ray, int values[4], int tex_x)
{
	double	step;
	double	tex_pos;
	int		tex_y;
	int		y;

	y = values[1];
	step = (double)TEXTURE / values[0];
	tex_pos = (y - HIGHT_OF_WIN / 2 + values[0] / 2) * step;
	while (y < values[2])
	{
		tex_y = (int)tex_pos & ((int)TEXTURE - 1);
		tex_pos += step;
		put_pixel_to_img_buffer(game->mlx_lib, values[3], y,
			texture_to_use_color(ray, game, tex_x, tex_y));
		y++;
	}
	return (y);
}

static void	draw_floor(t_game *game, int column, int y)
{
	while (y < HIGHT_OF_WIN)
	{
		put_pixel_to_img_buffer(game->mlx_lib, column, y,
			game->loaded_texture->f_color);
		y++;
	}
}

void	render_a_slice(t_game *game, t_ray *ray, int column, double ray_data[3])
{
	int	values[4];
	int	tex_x;
	int	y;

	get_draw_limits(ray_data[0], values);
	values[3] = column;
	tex_x = get_texture_x(game, ray, ray_data);
	draw_ceiling(game, column, values[1]);
	y = draw_wall(game, ray, values, tex_x);
	draw_floor(game, column, y);
}
