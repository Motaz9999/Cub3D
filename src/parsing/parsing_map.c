/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 03:19:34 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/05 06:19:38 by moodeh           ###   ########.fr       */
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

// this fun is for checking if the line have some trash value
// the allowed is line full of spaces
// or any line is form the set
// of allowed chars
int	check_line_map(char *line, char *set)
{
	int	i;

	if (line == NULL || *line == '\0' || *line == '\n')
		return (FALSE);
	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_strchr(set, line[i])) // its not from set return FALSE
			return (FALSE);
		i++;
	}
	return (TRUE);
}

// this fun is for copying the old content of the map to
// new map to add a new line
char	**copy_map_and_free(char **new_map, char **old_map, char *new_line,
		int hight)
{
	int	i;

	i = 0;
	new_map[hight] = NULL;
	while (i < hight - 1) // Copy elements up to the old height
	{
		new_map[i] = old_map[i];
		i++;
	}
	new_map[i] = new_line; // Add the new line at the end
	free(old_map);
	// Free the old array of pointers (not the strings themselves)
	return (new_map);
}

// must all lines under the map be full of spcaes only
// or just new lines
int	dose_the_map_ended(int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] != '\0')
		{
			// I added '\t' here in case you have empty tabs below the map
			if (!ft_strchr(" \t\n", line[i]))
			{
				free(line);
				return (FALSE);
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (TRUE);
}

// this fun is just for malloc the map inside the map
char	**make_map(int fd, char *first_row, char *set)
{
	char	**new_map;
	int		hight;
	char	*line;

	char **map; // i will realloc it multible times to get to the map hight
	new_map = NULL;
	hight = 1;
	map = malloc(sizeof(char *) * (hight + 1));
	map[hight] = NULL;  // end of the map
	map[0] = first_row; // first row of the map
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '\n') // ended the map
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
									data->map_data->map_char);// start with malloc the map to fill it up (open so_long file to remember)
    if (data->map_data->map == NULL)
    {
        return FALSE;
    }
	data->map_data->map_hight = get_hight(data->map_data->map);//test until here all works fine 
    // data->map_data->map = remake_map_to_rectangle(data->map_data);
    //     if (data->map_data->map == NULL)
    // {
    //     return FALSE;
    // }
	return (TRUE);
}
