/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:31:30 by moodeh            #+#    #+#             */
/*   Updated: 2026/06/19 20:11:11 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this fun is to know which side the ray going i mean
// like if the ray goes for right it must ++1 and for left --1
// and find the first value for side_dest_x
void	find_first_x(t_ray *ray, double ray_dir_x, double player_x, int map_x)
{
	if (ray_dir_x > 0)
	{
		ray->step_x = 1;
		ray->side_dest_x = ((map_x + 1.0) - player_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = -1;
		ray->side_dest_x = (player_x - map_x) * ray->delta_dist_x;
	}
}

// dont forgot
// if we go upside we --1 and if we goo down we ++1
// ray_dir_y < 0 means y is decreasing -> going UP towards y=0 (NORTH)
// ray_dir_y > 0 means y is increasing -> going DOWN away from y=0 (SOUTH)
void	find_first_y(t_ray *ray, double ray_dir_y, double player_y, int map_y)
{
	if (ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dest_y = (player_y - map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dest_y = ((map_y + 1.0) - player_y) * ray->delta_dist_y;
	}
}

// ok now we calc the ray len using DDA -> Digital Differential Analyzer
// so it work by finding diff between x1 x2 delta and y1 y2 delta
// so i have the player pos and the dir of the rays
// the next step is to make the ray traverse between grid bc i have a 2d map
// so we must know which square are we in (take the pos as int)
// this the first sq from the grid and the next Q is where we want to go?
// and btw bc we want to traverse inside the map i want a step_x ,step_y
t_ray	*dda(t_game *game, double ray_dir_x, double ray_dir_y)
{
	t_ray	*ray;
	int		map_x;
	int		map_y;

	ray = malloc(sizeof(t_ray));
	ft_memset((void *)ray, 0, sizeof(t_ray));
	// calculate delta_dist_x
	if (ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray_dir_x);
	// calculate delta_dist_y
	if (ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray_dir_y);
	ray->hit = 0;
	map_x = (int)game->player->x;
	map_y = (int)game->player->y;
	// setup the init values of side_dest
	find_first_x(ray, ray_dir_x, game->player->x, map_x);
	// the ray of x is so important way bc it tell u are left or right not up and down like y
	find_first_y(ray, ray_dir_y, game->player->y, map_y);
	while (ray->hit == 0)
	{
		//which side is closer(smaller)
		if (ray->side_dest_x < ray->side_dest_y)
		{
			ray->side_dest_x += ray->delta_dist_x;
			map_x += ray->step_x;
			ray->side = 1;
			// this important bc it till me about texture its like dose the wall hit a side wall(left or right) or a not side wall
			// why its with x ? imagin u r looking forward and the ray of u thats go right hit wall on ur right (so its will be a side wall bc its on x side)
		}
		else
		{
			ray->side_dest_y += ray->delta_dist_y;
			map_y += ray->step_y;
			ray->side = 0; // its mean i hit a wall that the player looking at
		}
		if (game->config_file_data->map_data->map[map_y][map_x] == '1')
			ray->hit = 1; // hit a wall
	}
	return (ray);
}

// if we are looking to side walls its hard look not normal
// and to avoid this problem(fish eye effect) we sub 1 delta from it to
// and the same for not side walls
// what i have
// |       |
//  \     /
//   \   /
//    \_/
// what i want
// |       |
// |       |
// |       |
// |       |
double	find_ray_len(t_ray *ray)
{
	double	ray_len;

	// if we hit a wall on the X axis (left or right side)
	if (ray->side == 1)
	{
		ray_len = ray->side_dest_x - ray->delta_dist_x;
	}
	// If we hit a wall on the Y axis (top or bottom side of a block)
	else
	{
		ray_len = ray->side_dest_y - ray->delta_dist_y;
	}
	return (ray_len);
}

// this fun is responsible for drawing rays coming from player to hit a wall
// btw the rays just coming from plane cam
// so ok if i want to render rays i must know the len of each ray and how many rays i have so
// this for 2d so i just want size of player * 2
// so i have double the size of rays
// ok the whole window its like a tall line coming from (-1 , 0 ,
//	1) so if the screen width 640 we want
// so CameraX have 3 values = 2x(x/width)-1  and x have the 3 values ->
//	-1 (left) , 0 (middle) , 1 (right)
// so the screen have 3divs 320 -> middle  0-319 left  321-640 right
// and if i want to shot the ray i must have dirs so know where the ray must go
// ok to find ray len i must know where he ends and where he starts
// he starts at player and end when hit a wall
// camerax is for know dir of the pixel
// why x/width bc i div the screen into percentage from 0 to 0.5 to 1->we are at the edge of the screen
// after i have a percentage i multiply it by 2 WHY? bc as i said i want the range from 1 ,
//	0 , -1 but now are 2 ,1 ,0
// so i minus 1 from it so it will be 1 , 0 , -1
// so camera x for knowing where the ray going so i can knows the dir of it
// ok there something we forget about ITS the angle between each ray
// next step is is calc the length form point to point
// SO FIRST ELEMENT WE be at camx = -1
// [أقصى يسار الشاشة]             [منتصف الشاشة]            [أقصى يمين الشاشة]
//          X-----------------------------X-----------------------------X
//           \                            ^                            /
//            \                           |                           /
//             \                          |                          /
//              \                         | dir                     /
//               \                        |                        /
//                \                       |                       /
//                 \                      |                      /
//                  \                     |                     /
//                   \                    |                    /
//                    \                   |                   /
//                     \                  |                  /
//                      \                 |                 /
//                       \_____________(اللاعب)____________/
//                        |  <----------- FOV ----------->
//						  |
//					here we start with came x = -1
void	render_as_3d(t_game *game)
{
	int i = 0;
	double ray_len;
	double ray_dir_x;
	double ray_dir_y;
	double camera_x;
	t_ray *ray;
	ray = NULL;
	while (i < WIDTH_OF_WIN)
	{
		camera_x = 2.0 * ((double)i / (double)WIDTH_OF_WIN) - 1.0;
		ray_dir_x = game->player->dir_x + (camera_x * game->player->plane_x);
		ray_dir_y = game->player->dir_y + (camera_x * game->player->plane_y);
		ray = dda(game, ray_dir_x, ray_dir_y);
		ray_len = find_ray_len(ray);
		// now this len i will use it to draw vertical line
		render_a_slice(game, ray, ray_len, i, ray_dir_x ,ray_dir_y);
		free(ray);
		ray = NULL;
		i++;
	}
}