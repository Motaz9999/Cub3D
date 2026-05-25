/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:31:30 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/25 21:39:22 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//so to find the ray len u must have a 2 points 
//first the player and second the wall and then u can calc the len between them 
//so this fun is called as much as i have (cols->x) it mean its the same size as the screen width
//btw to calc this u will minus the x1 from x2 and 
// double find_ray_len(double x_player , double y_player , double x_wall , double y_wall)
// {
    
// }

//ok each player have multi rays go from it
//we start from middle of the fit until 
double calc_ray_len(t_player *player)
{}

//this fun is responsible for drawing rays coming from player to hit a wall
//btw the rays just coming from plane cam
//so ok if i want to render rays i must know the len of each ray and how many rays i have so 
//this for 2d so i just want size of player * 2
//so i have double the size of rays
void draw_rays(int start_x ,int start_y ,int color ,t_game *game)
{
    int i = 0;
    double ray;
    while (i < (HITBOX * 2 * BLOCK) * 2)
    {
        ray = calc_ray_len(game->player);
        draw_ray(game->player , ray);
        i++;
    }
    
}