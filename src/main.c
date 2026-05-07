/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 21:10:46 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/07 06:40:29 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		exit(error_handling("Input:file dosent exist", 2));
	t_game game;
	ft_memset(&game, 0, sizeof(game));
	init_game(&game);
	game.config_file_data = parse_file(argv[1]);
}