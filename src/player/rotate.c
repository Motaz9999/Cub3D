/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 12:33:25 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/04 19:26:15 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//2D vector rotation
// this just change the dir of the player
// so if i look right the dir_x and dir_y changes
// so it ok if i look in any dir i want to look at
// btw each dir have value from 1-> -1
// what this mean like if u r looking forword then ur dirs are (0 , -1)
// and if u want to look right ur dirs are (1 , 0)
// what if u rotate to 45deg not 90 like half angel now
// u must calc new dir x and dir y
// btw here we use angels and (Xsin ,Ycos)
// and dot->its like speed value but for rotation
// so if u rotate for Right we multi play the cos(angel) 
// bc the we take from Y and add to x
// So to make clear if u r rotate left or Right 
// it will effect the ROT_SPEED bc we dont have angles here
//	-+
// the right is + and the left -
// now if i am want to rotate it will effect the horizontal and vertical
// first the horizontal -> X the x will have 2 values (X*cos(a) , X*sin(a))
// second the vertical -> Y and bc Y is in reverse here it will have minus
// so y -> (-Y*sin(a) , Y*cos(a))
// and if we combine both updates it will calc
// new x = X*cos(a) -Y*sin(a)
// new y = X*sin(a) + Y*cos(a)
// btw its also effect the plane of camera so they change with the dirs
//with clock dir
static void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = old_dir_x * cos(ROT_SPEED) - game->player->dir_y
		* sin(ROT_SPEED);
	game->player->dir_y = old_dir_x * sin(ROT_SPEED) + game->player->dir_y
		* cos(ROT_SPEED);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = old_plane_x * cos(ROT_SPEED) - game->player->plane_y
		* sin(ROT_SPEED);
	game->player->plane_y = old_plane_x * sin(ROT_SPEED) + game->player->plane_y
		* cos(ROT_SPEED);
}

//revers clock dir
static void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = old_dir_x * cos(-ROT_SPEED) - game->player->dir_y
		* sin(-ROT_SPEED);
	game->player->dir_y = old_dir_x * sin(-ROT_SPEED) + game->player->dir_y
		* cos(-ROT_SPEED);
	old_plane_x = game->player->plane_x;
	game->player->plane_x = old_plane_x * cos(-ROT_SPEED)
		- game->player->plane_y * sin(-ROT_SPEED);
	game->player->plane_y = old_plane_x * sin(-ROT_SPEED)
		+ game->player->plane_y * cos(-ROT_SPEED);
}

// ok if u want to move u must know 3 things
// speed
// direction
// plane FOV
void	handle_movement(t_game *game)
{
	if (game->keys->w == 1)
		move_forward(game);
	if (game->keys->s == 1)
		move_backward(game);
	if (game->keys->a == 1)
		strafe_left(game);
	if (game->keys->d == 1)
		strafe_right(game);
	if (game->keys->right_arrow == 1)
		rotate_right(game);
	if (game->keys->left_arrow == 1)
		rotate_left(game);
}
