/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 08:39:33 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/04 19:16:11 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this fun is for checking if the line have some trash value
// the allowed is line full of spaces
// or any line is form the set
// of allowed chars
static int	check_line_map(char *line, char *set)
{
	int	i;

	if (line == NULL || *line == '\0' || *line == '\n')
		return (FALSE);
	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_strchr(set, line[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

// this fun is for copying the old content of the map to
// new map to add a new line
static char	**copy_map_and_free(char **new_map, char **old_map, char *new_line,
		int hight)
{
	int	i;

	i = 0;
	new_map[hight] = NULL;
	while (i < hight - 1)
	{
		new_map[i] = old_map[i];
		i++;
	}
	new_map[i] = new_line;
	free(old_map);
	return (new_map);
}

// must all lines under the map be full of spcaes only
// or just new lines
static int	dose_the_map_ended(int fd)
{
	char	*line;
	int		i;
	int		is_valid;

	is_valid = TRUE;
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (is_valid && line[i] != '\0')
		{
			if (!ft_strchr(" \t\n", line[i]))
				is_valid = FALSE;
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (is_valid);
}

// this fun is just for malloc the map inside the map
char	**make_map(int fd, char *first_row, char *set)
{
	char	**new_map;
	int		hight;
	char	*line;
	char	**map;

	new_map = NULL;
	hight = 1;
	map = malloc(sizeof(char *) * (hight + 1));
	if (!map)
		return (NULL);
	map[hight] = NULL;
	map[0] = first_row;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '\n')
		{
			free(line);
			break ;
		}
		if (!check_line_map(line, set))
		{
			free(line);
			ft_free_all2((void **)map, NULL);
			error_handling("map line is invalid", (int)FALSE);
			return (NULL);
		}
		hight++;
		new_map = malloc(sizeof(char *) * (hight + 1));
		if (!new_map)
		{
			free(line);
			ft_free_all2((void **)map, NULL);
			error_handling("malloc new map", (int)FALSE);
			return (NULL);
		}
		map = copy_map_and_free(new_map, map, line, hight);
		new_map = NULL;
		line = get_next_line(fd);
	}
	if (!dose_the_map_ended(fd))
	{
		ft_free_all2((void **)map, NULL);
		error_handling("Write under tha map", (int)FALSE);
		return (NULL);
	}
	return (map);
}
