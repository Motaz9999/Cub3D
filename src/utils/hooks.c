/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 17:51:53 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/23 20:48:56 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//  KEY_W 119
// KEY_A 97
//  KEY_S 115
//  KEY_D 100
//  KEY_ESC 65307
// press button
int	handle_key_press(int key, void *game_void)
{
	t_game	*game;

	game = (t_game *)game_void;
	if (key == KEY_A)
		game->keys->a = 1;
	if (key == KEY_S)
		game->keys->s = 1;
	if (key == KEY_W)
		game->keys->w = 1;
	if (key == KEY_D)
		game->keys->d = 1;
	if (key == KEY_RIGHT)
		game->keys->right_arrow = 1;
	if (key == KEY_LEFT)
		game->keys->left_arrow = 1;
	if (key == KEY_ESC)
		close_game(game);
	return (0);
}

// unpresess button
int	handle_key_release(int key, void *game_void)
{
	t_game	*game;

	game = (t_game *)game_void;
	if (key == KEY_A)
		game->keys->a = 0;
	if (key == KEY_S)
		game->keys->s = 0;
	if (key == KEY_W)
		game->keys->w = 0;
	if (key == KEY_D)
		game->keys->d = 0;
	if (key == KEY_RIGHT)
		game->keys->right_arrow = 0;
	if (key == KEY_LEFT)
		game->keys->left_arrow = 0;
	return (0);
}

// this fun for init hook to use them with the window
// and to move using them
// what the user have keys here will be registered
// this fun is called before loop start
// we use mlx_hook to register keys and mlx_loop_hook to active them
// this fun also setup keys
int	setup_hooks(t_game *game)
{
	game->keys = malloc(sizeof(t_key));
	if (game->keys == NULL)
		return (error_handling("keys malloc", (int)FALSE));
	init_key(game->keys);
	mlx_hook(game->mlx_lib->win, 2, (1L << 0), handle_key_press, game);
	mlx_hook(game->mlx_lib->win, 3, (1L << 1), handle_key_release, game);
	mlx_hook(game->mlx_lib->win, 17, 0L, close_game, game); // x button
	mlx_loop_hook(game->mlx_lib->mlx, render, game);
	// render as mush it could to render
	return (TRUE);
}
