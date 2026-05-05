/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 02:43:11 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/05 05:09:58 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->config_file_data = NULL;
	game->player = NULL;
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->map_hight = 0;
	map->map_char = "01NSEW \n";//allowed chars for now to take line
}

void	init_config(t_config *config)
{
	int	i;

	config->fd = -1;
	config->count_of_elements = 0;
	config->save_line_map = NULL;
	config->map_data = NULL;
	i = 0;
	while (i < 6)
	{
		config->texture[i] = NULL;
		i++;
	}
}
