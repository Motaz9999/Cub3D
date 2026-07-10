/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 22:36:27 by samarnah          #+#    #+#             */
/*   Updated: 2026/07/10 22:42:30 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
// if we hit a wall on the X axis (left or right side)
//	if (ray->side == 1)
// else: If we hit a wall on the Y axis (top or bottom side of a block)
double	find_ray_len(t_ray *ray)
{
	if (ray->side == 1)
		return (ray->side_dest_x - ray->delta_dist_x);
	return (ray->side_dest_y - ray->delta_dist_y);
}

static void	get_ray_direction(t_game *game, int column,
		double ray_dir[2])
{
	double	camera_x;

	camera_x = 2.0 * ((double)column / (double)WIDTH_OF_WIN) - 1.0;
	ray_dir[0] = game->player->dir_x
		+ camera_x * game->player->plane_x;
	ray_dir[1] = game->player->dir_y
		+ camera_x * game->player->plane_y;
}

static void	render_column(t_game *game, int column)
{
	double	ray_dir[2];
	double	ray_data[3];
	t_ray	*ray;

	get_ray_direction(game, column, ray_dir);
	ray = dda(game, ray_dir[0], ray_dir[1]);
	if (!ray)
		return ;
	ray_data[0] = find_ray_len(ray);
	ray_data[1] = ray_dir[0];
	ray_data[2] = ray_dir[1];
	render_a_slice(game, ray, column, ray_data);
	free(ray);
}

// this fun is responsible for drawing rays coming from player to hit a wall
// btw the rays just coming from plane cam
// so ok if i want to render rays 
// i must know the len of each ray and how many rays i have so
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
// why x/width bc i div the screen into percentage 
// from 0 to 0.5 to 1->we are at the edge of the screen
// after i have a percentage i multiply it by 2 WHY? 
// bc as i said i want the range from 1 ,
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
	int	i;

	i = 0;
	while (i < WIDTH_OF_WIN)
	{
		render_column(game, i);
		i++;
	}
}
