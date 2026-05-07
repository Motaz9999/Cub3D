/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 03:19:34 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/07 10:20:59 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_hight(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}

int	get_width(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

// this fun is for finding the longest line (max)
static int	longest_line(t_map *map)
{
	int	longest;
	int	i;
	int	j;

	longest = 0;
	i = 0;
	while (i < map->map_hight)
	{
		j = ft_strlen(map->map[i]);
		if (longest < j)
			longest = j;
		i++;
	}
	return (longest);
}

int	parse_map(t_config *data)
{
	char	*saved_line;

	data->map_data = malloc(sizeof(t_map));
	if (!data->map_data)
		return (FALSE);
	init_map(data->map_data);
	saved_line = data->save_line_map;
	data->save_line_map = NULL;
	data->map_data->map = make_map(data->fd, saved_line,
			data->map_data->map_char);
	// start with malloc the map to fill it up (open so_long file to remember)
	if (data->map_data->map == NULL)
		return (FALSE);
	data->map_data->map_hight = get_hight(data->map_data->map);
	data->map_data->map_width = longest_line(data->map_data);
	data->map_data->map = remake_map(data->map_data);
	if (data->map_data->map == NULL)
		return (FALSE);
	if (!valid_map(data->map_data->map))
	 	return (FALSE);
	return (TRUE);
}
