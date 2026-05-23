/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 02:43:11 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/23 20:48:17 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->config_file_data = NULL;
	game->player = NULL;
	game->mlx_lib = NULL;
	game->loaded_texture = NULL;
	game->keys = NULL;
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->map_hight = 0;
	map->map_width = 0;
	map->map_char = "01NSEW \n"; // allowed chars for now to take line
	map->player_loc = malloc(sizeof(t_point));
	if (map->player_loc)
	{
		map->player_loc->x = -1;
		map->player_loc->y = -1;
	}
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

void	init_mlx_lib(t_mlx *mlx_lib)
{
	mlx_lib->mlx = NULL;
	mlx_lib->win = NULL;
	mlx_lib->img = NULL;
	mlx_lib->addr = NULL;
	mlx_lib->bpp = -1;
	mlx_lib->line_len = -1;
	mlx_lib->endian = -1;
}

void	init_texture(t_texture *texture)
{
	texture->no_texture = NULL;
	texture->so_texture = NULL;
	texture->we_texture = NULL;
	texture->ea_texture = NULL;
	texture->c_color = -1;
	texture->f_color = -1;
}

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