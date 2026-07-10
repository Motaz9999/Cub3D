/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 21:10:46 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/10 23:05:28 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	setup_game(t_game *game, char *file_name)
{
	init_game(game);
	game->config_file_data = parse_file(file_name);
	if (game->config_file_data == NULL)
		return (FALSE);
	setup_mlx(game);
	if (game->mlx_lib == NULL)
		return (FALSE);
	setup_texture(game);
	if (game->loaded_texture == NULL)
		return (FALSE);
	return (TRUE);
}

static void	loop(t_game *game)
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
		exit(error_handling("Input: file doesn't exist", 2));
	ft_memset(&game, 0, sizeof(game));
	if (!setup_game(&game, argv[1]))
	{
		clean_game(&game);
		exit(1);
	}
	loop(&game);
	clean_game(&game);
	return (0);
}
