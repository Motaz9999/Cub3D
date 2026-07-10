/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 22:35:40 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/04 20:10:42 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_data_value(char *path, t_type_of_text type)
{
	if (type != C && type != F)
		return (check_on_path(path));
	return (check_on_value(path));
}

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
	if (!check_data_value(path, type))
	{
		free(path);
		return (FALSE);
	}
	data->texture[(int)type] = path;
	data->count_of_elements++;
	return (TRUE);
}

static int	extract_texture_path(t_config *data, char *trim)
{
	if (ft_strncmp(trim, "NO ", 3) == 0)
		return (add_to_data(data, trim, NO, 3));
	if (ft_strncmp(trim, "SO ", 3) == 0)
		return (add_to_data(data, trim, SO, 3));
	if (ft_strncmp(trim, "WE ", 3) == 0)
		return (add_to_data(data, trim, WE, 3));
	if (ft_strncmp(trim, "EA ", 3) == 0)
		return (add_to_data(data, trim, EA, 3));
	return (-1);
}

static int	extract_color_value(t_config *data, char *trim)
{
	if (ft_strncmp(trim, "F ", 2) == 0)
		return (add_to_data(data, trim, F, 2));
	if (ft_strncmp(trim, "C ", 2) == 0)
		return (add_to_data(data, trim, C, 2));
	return (-1);
}

int	extract_data(t_config *data, char *line)
{
	char	*trim;
	int		status;

	trim = ft_strtrim(line, "\n \t");
	if (!trim)
		return (FALSE);
	status = extract_texture_path(data, trim);
	if (status == -1)
		status = extract_color_value(data, trim);
	if (status == -1)
	{
		error_handling("Invalid identifier", 2);
		status = FALSE;
	}
	free(trim);
	return (status);
}
