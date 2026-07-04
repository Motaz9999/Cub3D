/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 21:10:46 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/04 19:31:21 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop(t_game *game)
{
	if (!setup_hooks(game) || !setup_player(game))
	{
		clean_game(game);
		exit(1);
	}
	mlx_loop(game->mlx_lib->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit(error_handling("Input:file dosent exist", 2));
	ft_memset(&game, 0, sizeof(game));
	init_game(&game);
	game.config_file_data = parse_file(argv[1]);
	if (game.config_file_data == NULL)
	{
		clean_game(&game);
		exit(1);
	}
	setup_mlx(&game);
	if (game.mlx_lib == NULL)
	{
		clean_game(&game);
		exit(1);
	}
	setup_texture(&game);
	if (game.loaded_texture == NULL)
	{
		clean_game(&game);
		exit(1);
	}
	loop(&game);
	clean_game(&game);
	return (0);
}
