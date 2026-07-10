/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 22:40:28 by samarnah          #+#    #+#             */
/*   Updated: 2026/07/10 22:42:45 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this fun is to know which side the ray going i mean
// like if the ray goes for right it must ++1 and for left --1
// and find the first value for side_dest_x
void	find_first_x(t_ray *ray, double ray_dir_x, double player_x,
		int map_x)
{
	if (ray_dir_x > 0)
	{
		ray->step_x = 1;
		ray->side_dest_x = ((map_x + 1.0) - player_x)
			* ray->delta_dist_x;
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
void	find_first_y(t_ray *ray, double ray_dir_y, double player_y,
		int map_y)
{
	if (ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dest_y = (player_y - map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dest_y = ((map_y + 1.0) - player_y)
			* ray->delta_dist_y;
	}
}
