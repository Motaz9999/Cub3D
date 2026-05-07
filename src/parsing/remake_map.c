/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 08:44:14 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/07 10:21:49 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this fun is take a line
// and find the longest line
// then make new lines that are copy of the old one
// then give it same length as the newest one
static char	*normalize_line(char *line, int longest)
{
	char	*new_line;
	int		i;

	new_line = malloc(longest + 1);
	if (new_line == NULL)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < longest)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[longest] = '\0';
	return (new_line);
}

// take the old map and make it rectangle
// the only thing its haves is chars from the map and spaces
char	**remake_map(t_map *map)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (map->map_hight + 1));
	if (new_map == NULL)
	{
		error_handling("new map malloc", 2);
		return (NULL);
	}
	i = 0;
	while (i < map->map_hight)
	{
		new_map[i] = NULL;
		new_map[i] = normalize_line(map->map[i], map->map_width);
		if (new_map[i] == NULL)
		{
			ft_free_all2((void **)new_map, NULL);
			error_handling("new line for new map", 2);
			return (NULL);
		}
		i++;
	}
	new_map[i] = NULL;
	ft_free_all2((void **)map->map, NULL);
	return (new_map);
}
