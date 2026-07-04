/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 22:35:40 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/04 19:21:08 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// add new path and
// checks if i already added this path
// and take the path
int	add_to_data(t_config *data, char *extract_path, t_type_of_text type,
		int skip)
{
	char	*path;

	if (data->texture[(int)type] != NULL)
		return (error_handling("Duplicates texture paths", (int)FALSE));
	path = ft_strtrim(extract_path + skip, " \t\n");
	if (path == NULL)
	{
		error_handling("strtrim", 2);
		return (FALSE);
	}
	if ((type != C && type != F) && !check_on_path(path))
	{
		free(path);
		return (FALSE);
	}
	else if ((type == C || type == F) && !check_on_value(path))
	{
		free(path);
		return (FALSE);
	}
	data->texture[(int)type] = path;
	data->count_of_elements++;
	return (TRUE);
}

// this fun is for searching for the something i needs and it starts with
// NO//SO//WE//EA//F//C
int	extract_data(t_config *data, char *line)
{
	char	*trim;
	int		status;

	trim = ft_strtrim(line, "\n \t");
	if (!trim)
		return (FALSE);
	status = TRUE;
	if (ft_strncmp(trim, "NO ", 3) == 0)
		status = add_to_data(data, trim, NO, 3);
	else if (ft_strncmp(trim, "SO ", 3) == 0)
		status = add_to_data(data, trim, SO, 3);
	else if (ft_strncmp(trim, "WE ", 3) == 0)
		status = add_to_data(data, trim, WE, 3);
	else if (ft_strncmp(trim, "EA ", 3) == 0)
		status = add_to_data(data, trim, EA, 3);
	else if (ft_strncmp(trim, "F ", 2) == 0)
		status = add_to_data(data, trim, F, 2);
	else if (ft_strncmp(trim, "C ", 2) == 0)
		status = add_to_data(data, trim, C, 2);
	else
	{
		error_handling("Invalid identifier", 2);
		status = FALSE;
	}
	free(trim);
	return (status);
}
