/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 22:19:32 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/04 03:15:59 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this file for checking on the extention of the file
//this to check on path extension
//use it later U can added to libft
int check_extension(char *path, char *ext)
{
    int len;
    int ext_len;

    if (!path || !ext)
        return (FALSE);
    len = ft_strlen(path);
    ext_len = ft_strlen(ext);
    if (len < ext_len)
        return (FALSE);
    if (ft_strncmp(&path[len - ext_len], ext, ext_len) == 0 ) 
    return TRUE;
    else
    return (FALSE);
}

//check of the line is part of the map (have all the map chars or some of them)
static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

// check if the line have some char must not have or check on the line is from the map or not in the same time
int	line_have_trash(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (FALSE);
	if (!ft_strncmp(&line[i], "NO ", 3) || !ft_strncmp(&line[i], "SO ", 3)
		|| !ft_strncmp(&line[i], "WE ", 3) || !ft_strncmp(&line[i], "EA ", 3)
		|| !ft_strncmp(&line[i], "F ", 2) || !ft_strncmp(&line[i], "C ", 2))
		return (FALSE);
	if (is_map_line(line))
		return (FALSE);
	error_handling("Line contains trash values", 2);
	return (TRUE); // has trash value
}

// just skip
int	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '\t' && line[i] != ' ')
			// this mean that i have data on the line
			return (FALSE);
		i++;
	}
	return (TRUE); // this mean that the file is empty
}



// this fun is for gathering multible checks on map
// first check is on the file have data i want
// this fun must read all the lines before coming to the map if
// it comes to the map (like have a line start with the char not from those
// NO ./path/north.xpm — north texture path
// SO ./path/south.xpm — south texture path
// WE ./path/west.xpm — west texture path
// EA ./path/east.xpm — east texture path
// F 220,100,0 — floor RGB color
// C 225,30,0 — ceiling RGB color
// so when i hit spaces with zeros and ones this mean i am inside the map
// and i must check on the counter element
// u also must check on duplicates
// btw must be empty after the map
// must the line dont have trash values (dont start with something we dont know)
static int	fill_data(t_config *data)
{
	char *line;// take line by line (skip the empty lines or the one have trash values)
	line = get_next_line(data->fd);
	while (line != NULL)
	{
		if (line_is_empty(line))
		{
			free(line);
			line = get_next_line(data->fd);
			continue ;
		}
		else if (line_have_trash(line))
		{
			free(line);
			return (FALSE);
		}
		else if (is_map_line(line))
		{
			if (data->count_of_elements != 6)
			{
				free(line);
				return error_handling("starts the map without having all texture element" , (int)FALSE);
			}
			data->save_line_map = line;
			break ;
		}
		else if (!extract_data(data, line))
		{
			free(line);
			return (FALSE);
		}
		free(line);
		line = get_next_line(data->fd);
	}
	return (TRUE);
}

static void	init_data(t_config *data)
{
	int	i;

	data->fd = -1;
	data->count_of_elements = 0;
	data->save_line_map = NULL;
	data->map = NULL;
	i = 0;
	while (i < 6)
	{
		data->texture[i] = NULL;
		i++;
	}
}

t_config	*parse_file(char *file_name)
{
	t_config	*data;

	data = malloc(sizeof(t_config));
	// now i have element that can store data so lets start
	if (data == NULL)
		exit(error_handling("Malloc error", 2));
	init_data(data);// first test to see if i can open fd
	if (!check_extension(file_name , ".cub"))
	{
		free(data);
		exit(error_handling("Wrong file name extention", 2));
	}
	data->fd = open(file_name, O_RDONLY);
	if (data->fd == -1)
	{
		free(data);
		exit(error_handling("File not found or couldn't access", 2));
	} // now i have an open file so
	if (!fill_data(data))
	{
		clean_data(data);
		exit(2);
	}
	return (data);
}
