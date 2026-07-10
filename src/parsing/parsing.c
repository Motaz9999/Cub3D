/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 22:19:32 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/10 21:20:21 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define MAP_STARTED 2

static int	set_map_start(t_config *data, char *line)
{
	if (data->count_of_elements != 6)
	{
		free(line);
		return (error_handling("starts the map without having "
				"all texture element", (int)FALSE));
	}
	data->save_line_map = line;
	return (MAP_STARTED);
}

static int	process_config_line(t_config *data, char *line)
{
	if (line_is_empty(line))
	{
		free(line);
		return (TRUE);
	}
	if (line_have_trash(line))
	{
		free(line);
		return (FALSE);
	}
	if (is_map_line(line))
		return (set_map_start(data, line));
	if (!extract_data(data, line))
	{
		free(line);
		return (FALSE);
	}
	free(line);
	return (TRUE);
}

static int	check_complete_data(t_config *data)
{
	if (data->count_of_elements != 6)
		return (error_handling("the file dosent have all required info",
				(int)FALSE));
	if (data->count_of_elements == 6 && data->save_line_map == NULL)
		return (error_handling("missing map", (int)FALSE));
	return (TRUE);
}

static int	fill_data(t_config *data)
{
	char	*line;
	int		status;

	line = get_next_line(data->fd);
	while (line != NULL)
	{
		status = process_config_line(data, line);
		if (status == FALSE)
			return (FALSE);
		if (status == MAP_STARTED)
			break ;
		line = get_next_line(data->fd);
	}
	return (check_complete_data(data));
}

t_config	*parse_file(char *file_name)
{
	t_config	*data;

	data = malloc(sizeof(t_config));
	if (data == NULL)
		exit(error_handling("Malloc error", 2));
	init_config(data);
	if (!check_extension(file_name, ".cub"))
	{
		free(data);
		exit(error_handling("Wrong file name extention", 2));
	}
	data->fd = open(file_name, O_RDONLY);
	if (data->fd == -1)
	{
		free(data);
		exit(error_handling("File not found or couldn't access", 2));
	}
	if (!fill_data(data) || !check_texture(data) || !parse_map(data))
	{
		clean_data(data);
		exit(2);
	}
	return (data);
}
