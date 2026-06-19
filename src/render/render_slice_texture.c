/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_slice_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:07:38 by moodeh            #+#    #+#             */
/*   Updated: 2026/06/19 20:19:36 by moodeh           ###   ########.fr       */
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
int	texture_to_use_color(t_ray *ray , t_game *game , int tex_x , int tex_y)
{
	if (ray->side == 1)
	{
		if (ray->step_x > 0) // right
			{return (game->loaded_texture->ea_texture[tex_y][tex_x]);}
		else
			{return (game->loaded_texture->we_texture[tex_y][tex_x]);}
	}
	else
	{
		if (ray->step_y < 0)
			{return (game->loaded_texture->no_texture[tex_y][tex_x]);}
		else
			{return  (game->loaded_texture->so_texture[tex_y][tex_x]);}
	}
}

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
// after testing and seeing all things work fine now we continue with texture not color
// so every texture size is 64x64 so its easy to put them together
// not that easy bc u need to know which column to take from the texture
// and secound which texture to use
void	render_a_slice(t_game *game, t_ray *ray, double ray_len, int i_in_width , double ray_dir_x , double ray_dir_y)
{
	int	hight_of_texture;
	int	draw_start;
	int	draw_end;
	int	i;
	int tex_x;
	int tex_y;
	// int	texture_type;
	i = 0;
	hight_of_texture = (int)(HIGHT_OF_WIN / ray_len);
	draw_start = (-hight_of_texture / 2) + (HIGHT_OF_WIN / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (hight_of_texture / 2) + (HIGHT_OF_WIN / 2);
	if (draw_end >= HIGHT_OF_WIN)
		draw_end = HIGHT_OF_WIN;
	//which col of the img did the ray hit tex_x
	double exact_hit;
	
	//must know which wall the ray hit
	if (ray->side == 1)//hit vertical wall
	exact_hit = game->player->y * (ray_len *ray_dir_y);
	else //hit horizontal wall
	exact_hit = game->player->x * (ray_len *ray_dir_x); 
	//after knowing which wall being hit we want to know how many of the wall being hit
	double precentage = exact_hit - floor(exact_hit);//its for knowing exactly where it hit the wall like if i have a wall number 5 and the ray hit 5.6 so  hit 60% of the way down that block.
		// Flip texture if looking South or West so it's not mirrored
	tex_x = (int)(precentage * TEXTURE);// we must draw the pixels from 60% of the way across the texture image = 38.4 so we take col number 38 (the whole col)
	if (ray->side == 0 && ray_dir_y > 0)
		tex_x = TEXTURE - tex_x - 1;
	if (ray->side == 1 && ray_dir_x < 0)
		tex_x = TEXTURE - tex_x - 1;
	//the tex_x have 64 pixel in total widths 
	// imagin we the height of texture is 300 pixel and the my are is 64 pixel how can i draw it?
	//stretch it like in array we moving 1 by 1 now i will be moving TEXTURE/hight_of_texture each time
	//64/300 =0.213
	// ceiling
	double step = TEXTURE / hight_of_texture;
		double tex_pos = (draw_start - HIGHT_OF_WIN / 2 + hight_of_texture / 2) * step;
	while (i < draw_start)
	{
		put_pixel_to_img_buffer(game->mlx_lib, i_in_width, i,
			game->loaded_texture->c_color);
		i++;
	}
	// texture
	while (i < draw_end)
	{
		 tex_y = (int)tex_pos & ((int)TEXTURE -1);
		tex_pos +=step;
	
		put_pixel_to_img_buffer(game->mlx_lib, i_in_width, i,	texture_to_use_color(ray , game,tex_x , tex_y) );
		i++;
	}
	// floor
	while (i < HIGHT_OF_WIN)
	{
		put_pixel_to_img_buffer(game->mlx_lib, i_in_width, i,
			game->loaded_texture->f_color);
		i++;
	}
}
