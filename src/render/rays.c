/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:31:30 by moodeh            #+#    #+#             */
/*   Updated: 2026/06/16 11:05:09 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//ok now we calc the ray len using DDA -> Digital Differential Analyzer
//so it work by finding diff between x1 x2 delta and y1 y2 delta
//so i have the player pos and the dir of the rays
//the next step is to make the ray traverse between grid bc i have a 2d map
//so we must know which square are we in (take the pos as int)
//this the first sq from the grid and the next Q is where we want to go?
//and btw bc we want to traverse inside the map i want a step_x ,step_y 
double	calc_ray_len(t_game *game, double ray_dir_X , double  ray_dir_y)
{
	
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
//SO FIRST ELEMENT WE be at camx = -1
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
//                        |<----------- FOV ----------->
//					here we start with came x = -1

void	draw_rays(int start_x, int start_y, int color, t_game *game)
{
	int i = 0;
	double ray_len;
	double ray_dir_x;
	double ray_dir_y;
	double camera_x;
	while (i < WIDTH_OF_WIN)
	{
		camera_x = 2 * ((double)i / WIDTH_OF_WIN) - 1;
		ray_dir_x = game->player->dir_x + (camera_x * game->player->plane_x);
		ray_dir_y = game->player->dir_y + (camera_x * game->player->plane_y);
		ray_len = calc_ray_len(game,ray_dir_x, ray_dir_y);
		draw_ray(game, ray_len, ray_dir_x, ray_dir_y);
		i++;
	}
}