/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:56:19 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/25 14:41:18 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this fun his job to see if the place the player want to move for is valid place or not
// so if the player move to new block we update the previous map into new with new plyer loc
// why the here are x and y so
static int	check_move_to_block(double x, double y, t_map *map_data, t_player *player)
{
	int		old_loc_x;
	int		old_loc_y;
	char	*c;

	if (map_data->map[(int)y][(int)x] == '1')
		return (FALSE);
	if (map_data->map[(int)y][(int)x] == '0') // here i must update the map
	{
		old_loc_x = (int)player->x;
		old_loc_y = (int)player->y;
		c = map_data->map[old_loc_y][old_loc_x];
		map_data->map[old_loc_y][old_loc_x] = '0';
		map_data->map[(int)y][(int)x] = c;
	}
	return (TRUE);
}

// if we want to go left we must move in 2d and imagin moving in 3d
// so i have here a speed and a dir so now i can move
// but before i move i must checks if i can move to that center so i can enter
// the wall
// dont forget in map u have chars (0 , 1 , player)
// so when u move
// and remember each point are a full box have a size of (1.0 x 1.0) this mean the
// point 3.0 , 5.0 have spaces (3.0-3.99) , (5.0 - 5.99) before change the box
// and each time i move with a static speed and
// the move forword is meaning that i walk straight line
// so why i use multiply by dir cus i want to always make sure that
// w is move forword regardless what face the player respowend with
// and then i check the new point if it valid place i can move to
// and why its + not -? bc its moveforward like what if the dir x are
//	-1 or dir y -1
// this mean(- + -)-> (bigger -) that i will move back not forword
// the buffer is for map collision ,
//	so if i so close of the wall i dont want to make the
// distance between the player and
// the wall ZERO if it is it will make a problem with rendering the map in the right way
// btw when u press W,S u r moving on the  same line u see so there is no need to do anything with the dirs just add or just minis
// 0deg where i am looking
void	move_forword(t_game *game)
{
	double	check_x;
	double	check_y;
	double	buffer;

	buffer = 0.2;
	check_x = game->player->x + (game->player->dir_x * (MOVE_SPEED + buffer));
	if (check_move_to_block(check_x, game->player->y,
			game->config_file_data->map_data, game->player))
	{
		game->player->x += game->player->dir_x * MOVE_SPEED;
	}
	// current loc + (speed +buffer) * current dir) how many i can move
	check_y = game->player->y + (game->player->dir_y * (MOVE_SPEED + buffer));
	if (check_move_to_block(game->player->x, check_y,
			game->config_file_data->map_data, game->player))
	{
		game->player->y += game->player->dir_x * MOVE_SPEED;
	}
}

void	move_backword(t_game *game)
{
	double	check_x;
	double	check_y;
	double	buffer;

	buffer = 0.2;
	check_x = game->player->x - (game->player->dir_x * (MOVE_SPEED + buffer));
	if (check_move_to_block(check_x, game->player->y,
			game->config_file_data->map_data, game->player))
	{
		game->player->x -= game->player->dir_x * MOVE_SPEED;
	}
	// current loc + (speed +buffer) * current dir) how many i can move
	check_y = game->player->y - (game->player->dir_y * (MOVE_SPEED + buffer));
	if (check_move_to_block(game->player->x, check_y,
			game->config_file_data->map_data, game->player))
	{
		game->player->y -= game->player->dir_x * MOVE_SPEED;
	}
}

// now the player goes to left
// here the player move in the same X or Y
// so again we use dir to see where we are moving
// and using X,Y so here another story we move like 90deg from where i am looking
// here we use a simple trick called
// a perpendicular vector (x,y)-> (-y ,x)
// so when we do dot prodect with the 2s we find that =0
//    ( (x,y) . (-y ,x) == 0)
void	strafe_left(t_game *game)
{
	double	check_x;
	double	check_y;
	double	prop_x;
	double	prop_y;
	double	buffer;

	buffer = 0.2;
	prop_x = -game->player->dir_y;
	prop_y = game->player->dir_x;
	check_x = game->player->x - (prop_x * (buffer + MOVE_SPEED));
	if (check_move_to_block(check_x, game->player->y,
			game->config_file_data->map_data, game->player))
	{
		game->player->x -= prop_x * (buffer + MOVE_SPEED);
	}
	// current loc + (speed +buffer) * current dir) how many i can move
	check_y = game->player->y - (prop_y * (MOVE_SPEED + buffer));
	if (check_move_to_block(game->player->x, check_y,
			game->config_file_data->map_data, game->player))
	{
		game->player->y -= prop_y * (MOVE_SPEED + buffer);
	}
}

void	strafe_right(t_game *game)
{
	double	check_x;
	double	check_y;
	double	prop_x;
	double	prop_y;
	double	buffer;

	buffer = 0.2;
	prop_x = -game->player->dir_y;
	prop_y = game->player->dir_x;
	check_x = game->player->x + (prop_x * (buffer + MOVE_SPEED));
	if (check_move_to_block(check_x, game->player->y,
			game->config_file_data->map_data, game->player))
	{
		game->player->x += prop_x * (buffer + MOVE_SPEED);
	}
	// current loc + (speed +buffer) * current dir) how many i can move
	check_y = game->player->y + (prop_y * (MOVE_SPEED + buffer));
	if (check_move_to_block(game->player->x, check_y,
			game->config_file_data->map_data, game->player))
	{
		game->player->y += prop_y * (MOVE_SPEED + buffer);
	}
}



