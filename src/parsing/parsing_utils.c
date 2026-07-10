/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 21:19:00 by samarnah          #+#    #+#             */
/*   Updated: 2026/07/10 21:19:51 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define MAP_STARTED 2

int	check_extension(char *path, char *ext)
{
	int	len;
	int	ext_len;

	if (!path || !ext)
		return (FALSE);
	len = ft_strlen(path);
	ext_len = ft_strlen(ext);
	if (len < ext_len)
		return (FALSE);
	if (ft_strncmp(&path[len - ext_len], ext, ext_len) == 0)
		return (TRUE);
	return (FALSE);
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	is_identifier(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3))
		return (TRUE);
	if (!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (TRUE);
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (TRUE);
	return (FALSE);
}

int	line_have_trash(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (FALSE);
	if (is_identifier(&line[i]))
		return (FALSE);
	if (is_map_line(line))
		return (FALSE);
	error_handling("Line contains trash values", 2);
	return (TRUE);
}

int	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '\t' && line[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
