/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 21:22:50 by samarnah          #+#    #+#             */
/*   Updated: 2026/07/10 21:28:46 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**init_map_array(char *first_row)
{
	char	**map;

	map = malloc(sizeof(char *) * 2);
	if (!map)
		return (NULL);
	map[0] = first_row;
	map[1] = NULL;
	return (map);
}

char	**line_map_error(char **map, char *line)
{
	free(line);
	ft_free_all2((void **)map, NULL);
	error_handling("map line is invalid", (int)FALSE);
	return (NULL);
}

char	**end_map_error(char **map)
{
	ft_free_all2((void **)map, NULL);
	error_handling("Write under tha map", (int)FALSE);
	return (NULL);
}

char	**append_line_to_map(char **map, char *line, int hight)
{
	char	**new_map;

	new_map = malloc(sizeof(char *) * (hight + 1));
	if (!new_map)
	{
		free(line);
		ft_free_all2((void **)map, NULL);
		error_handling("malloc new map", (int)FALSE);
		return (NULL);
	}
	return (copy_map_and_free(new_map, map, line, hight));
}
