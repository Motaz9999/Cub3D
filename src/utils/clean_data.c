/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 02:50:38 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/02 02:55:57 by moodeh           ###   ########.fr       */
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
	free(map);
}

//this fun is for clean the config data file 
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
	if (data->map != NULL)
		clean_map(data->map);
	free(data);
}
