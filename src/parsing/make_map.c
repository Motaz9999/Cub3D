/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 08:39:33 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/10 23:44:23 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**copy_map_and_free(char **new_map, char **old_map, char *new_line,
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

static int	add_map_line(char ***map, char *line, char *set, int *hight)
{
	if (!check_line_map(line, set))
	{
		*map = line_map_error(*map, line);
		return (FALSE);
	}
	(*hight)++;
	*map = append_line_to_map(*map, line, *hight);
	if (!*map)
		return (FALSE);
	return (TRUE);
}

char	**make_map(int fd, char *first_row, char *set)
{
	char	*line;
	char	**map;
	int		hight;

	hight = 1;
	map = init_map_array(first_row);
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL && *line != '\n')
	{
		if (!add_map_line(&map, line, set, &hight))
			return (NULL);
		line = get_next_line(fd);
	}
	if (line != NULL)
		free(line);
	if (!dose_the_map_ended(fd))
		return (end_map_error(map));
	return (map);
}
