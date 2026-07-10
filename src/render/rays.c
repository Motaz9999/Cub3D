/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:31:30 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/10 22:41:31 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ok now we calc the ray len using DDA -> Digital Differential Analyzer
// so it work by finding diff between x1 x2 delta and y1 y2 delta
// so i have the player pos and the dir of the rays
// the next step is to make the ray traverse between grid bc i have a 2d map
// so we must know which square are we in (take the pos as int)
// this the first sq from the grid and the next Q is where we want to go?
// and btw bc we want to traverse inside the map i want a step_x ,step_y
// calculate delta_dist_x
//	if (ray_dir_x == 0)
//		ray->delta_dist_x = 1e30;
//	else
//		ray->delta_dist_x = fabs(1 / ray_dir_x);
// calculate delta_dist_y
//	if (ray_dir_y == 0)
//		ray->delta_dist_y = 1e30;
//	else
//		ray->delta_dist_y = fabs(1 / ray_dir_y);
// setup the init values of side_dest
//	find_first_x(ray, ray_dir_x, game->player->x, map_x);
// the ray of x is so important way bc 
// it tell u are left or right not up and down like y
//	find_first_y(ray, ray_dir_y, game->player->y, map_y);
//which side is closer(smaller)
//		if (ray->side_dest_x < ray->side_dest_y)
//{
//			ray->side_dest_x += ray->delta_dist_x;
//			map_x += ray->step_x;
//			ray->side = 1;
// this important bc it till me about texture its like dose 
// the wall hit a side wall(left or right) or a not side wall
// why its with x ? imagin u r looking forward and the ray of u 
// thats go right hit wall on ur right 
// (so its will be a side wall bc its on x side)
//		else
//			ray->side = 0; its mean i hit a wall that the player looking at
// 			ray->hit = 1; // hit a wall
static void	set_delta_dist(t_ray *ray, double ray_dir_x,
		double ray_dir_y)
{
	if (ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray_dir_x);
	if (ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray_dir_y);
}

static void	move_ray(t_ray *ray, int map_pos[2])
{
	if (ray->side_dest_x < ray->side_dest_y)
	{
		ray->side_dest_x += ray->delta_dist_x;
		map_pos[0] += ray->step_x;
		ray->side = 1;
	}
	else
	{
		ray->side_dest_y += ray->delta_dist_y;
		map_pos[1] += ray->step_y;
		ray->side = 0;
	}
}

static void	run_dda(t_game *game, t_ray *ray, int map_pos[2])
{
	while (ray->hit == 0)
	{
		move_ray(ray, map_pos);
		if (game->config_file_data->map_data
			->map[map_pos[1]][map_pos[0]] == '1')
			ray->hit = 1;
	}
}

t_ray	*dda(t_game *game, double ray_dir_x, double ray_dir_y)
{
	t_ray	*ray;
	int		map_pos[2];

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ft_memset(ray, 0, sizeof(t_ray));
	set_delta_dist(ray, ray_dir_x, ray_dir_y);
	map_pos[0] = (int)game->player->x;
	map_pos[1] = (int)game->player->y;
	find_first_x(ray, ray_dir_x, game->player->x, map_pos[0]);
	find_first_y(ray, ray_dir_y, game->player->y, map_pos[1]);
	run_dda(game, ray, map_pos);
	return (ray);
}
