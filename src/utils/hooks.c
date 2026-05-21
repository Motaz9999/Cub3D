/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 17:51:53 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/21 18:31:49 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
//  KEY_W 119
// KEY_A 97
//  KEY_S 115
//  KEY_D 100
//  KEY_ESC 65307
int	handle_keypress(int key, void *game_void)
{
	t_game	*game;

	game = (t_game *)game_void;
	if (key == KEY_ESC)
		return (close_game(game));
	//	else if (key == KEY_A)
	//		else if (key == KEY_D) else if (key == KEY_S) else if (key == KEY_W)
	return (0);
}

// this fun for init hook to use them with the window
// and to move using them
// what the user have keys here will be registered
// this fun is called before loop start
// we use mlx_hook to register keys and mlx_loop_hook to active them
int	setup_hooks(t_game *game)
{
	mlx_key_hook(game->mlx_lib->win, handle_keypress, game);//where u moves and looks   
	// keys on keyboard
    //mlx_mouse_hook(game->mlx_lib->win ,handle_mouse ,game);//where u looks
	mlx_hook(game->mlx_lib->win, 17, (1L << 0), close_game, game); // x button
	mlx_loop_hook(game->mlx_lib->mlx, render, game);      // render as mush it could to render
	return (TRUE);
}
