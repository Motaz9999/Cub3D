/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 02:50:38 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/10 22:43:07 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clean_map(t_map *map)
{
	int	i;

	if (map == NULL)
		return ;
	if (map->map != NULL)
	{
		i = 0;
		while (map->map[i] != NULL)
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	if (map->player_loc != NULL)
		free(map->player_loc);
	free(map);
}

// this fun is for clean the config data file
void	clean_data(t_config *data)
{
	int	i;

	if (data == NULL)
		return ;
	if (data->fd != -1)
		close(data->fd);
	if (data->save_line_map != NULL)
		free(data->save_line_map);
	i = 0;
	while (i < 6)
	{
		if (data->texture[i] != NULL)
			free(data->texture[i]);
		i++;
	}
	if (data->map_data != NULL)
		clean_map(data->map_data);
	free(data);
}

void	clean_mlx_data(t_mlx *mlx_lib)
{
	if (mlx_lib == NULL)
		return ;
	if (mlx_lib->img != NULL)
		mlx_destroy_image(mlx_lib->mlx, mlx_lib->img);
	if (mlx_lib->win != NULL)
		mlx_destroy_window(mlx_lib->mlx, mlx_lib->win);
	if (mlx_lib->mlx != NULL)
	{
		mlx_destroy_display(mlx_lib->mlx);
		free(mlx_lib->mlx);
	}
	free(mlx_lib);
}

void	clean_texture(void *mlx_ptr, t_texture *texture)
{
	if (texture == NULL)
		return ;
	(void)mlx_ptr;
	if (texture->no_texture != NULL)
		ft_free_all2((void **)texture->no_texture, NULL);
	if (texture->so_texture != NULL)
		ft_free_all2((void **)texture->so_texture, NULL);
	if (texture->we_texture != NULL)
		ft_free_all2((void **)texture->we_texture, NULL);
	if (texture->ea_texture != NULL)
		ft_free_all2((void **)texture->ea_texture, NULL);
	free(texture);
}

void	clean_game(t_game *game)
{
	void	*mlx_ptr;

	if (game == NULL)
		return ;
	mlx_ptr = NULL;
	if (game->mlx_lib != NULL)
		mlx_ptr = game->mlx_lib->mlx;
	if (game->loaded_texture != NULL)
		clean_texture(mlx_ptr, game->loaded_texture);
	if (game->mlx_lib != NULL)
		clean_mlx_data(game->mlx_lib);
	if (game->config_file_data != NULL)
		clean_data(game->config_file_data);
	if (game->keys != NULL)
		free(game->keys);
	if (game->player != NULL)
		free(game->player);
}
