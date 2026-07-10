/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 21:51:03 by samarnah          #+#    #+#             */
/*   Updated: 2026/07/10 21:53:22 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// clean_data
int	close_game(void *game_void)
{
	t_game	*game;

	game = (t_game *)game_void;
	if (game != NULL)
	{
		clean_game(game);
		exit(0);
	}
	return (0);
}

// init_game
void	init_key(t_key *keys)
{
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->w = 0;
	keys->right_arrow = 0;
	keys->left_arrow = 0;
}

void	init_player(t_player *player)
{
	player->x = 0.0;
	player->y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->plane_len = 0.0;
}
