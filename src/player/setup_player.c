/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:32:13 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/23 20:36:32 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this is take the face of player N,E,W,S and convert it into value
void	setup_dir_player(t_player *player, char player_face)
{
	if (player_face == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1.0;
	}
	else if (player_face == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1.0;
	}
	else if (player_face == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
	}
	else if (player_face == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0;
	}
}

void	setup_plane(t_player *player, char player_face)
{
	if (player_face == 'N')
	{
		player->plane_x = 0;
		player->plane_y = -player->plane_len;
	}
	else if (player_face == 'S')
	{
		player->plane_x = 0;
		player->plane_y = player->plane_len;
	}
	else if (player_face == 'E')
	{
		player->plane_x = player->plane_len;
		player->plane_y = 0;
	}
	else if (player_face == 'W')
	{
		player->plane_x = -player->plane_len;
		player->plane_y = 0;
	}
}

// this fun calc plane from the FOV angle u givin
// we div the FOV on 2 WHY bc the fov is right triangle and left so there are 2 triangles
// next step is from angle to radian so the computer can understand it well
// so we multiply it with PI/180
// the tan to calc the len of plane ()
void	calc_plane(t_player *player)
{
	double	rad;

	rad = FOV_DIG / 2;
	rad = rad * (M_PI / 180);
	player->plane_len = tan(rad);
}

// the +0.5 bc i dont want the player to start at the boundary of the (x, y)
int	setup_player(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (game->player == NULL)
		return (error_handling("malloc player data", (int)FALSE));
	init_player(game->player);
	game->player->x = (double)game->config_file_data->map_data->player_loc->x
		+ 0.5;
	game->player->y = (double)game->config_file_data->map_data->player_loc->y
		+ 0.5;
	// now i have x and y on map next i want the dir of x and y
	calc_plane(game->player);
	setup_dir_player(game->player,
		game->config_file_data->map_data->player_face);
	setup_plane(game->player, game->config_file_data->map_data->player_face);
	return (TRUE);
}
