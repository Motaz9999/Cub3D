/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 22:35:40 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/03 22:43:21 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//add new path and 
// checks if i already added this path 
//and take the path 
int add_to_data(t_config *data,char *extract_path , t_type_of_text type, int skip)
{
	if (data->texture[(int)type] != NULL)
	{
		error_handling("Duplicates" , 2);
		return FALSE;
	}
	char *path = ft_strdup(ft_strtrim(extract_path+skip , " \t"));//now i must have clear str path and save it
	if ( path == NULL)
	{
		error_handling("strdup" , 2);
		return FALSE;
	}
	if ((type != C && type !=  F ) && !check_on_path(path))//to check on path 
	{
		error_handling("Path" , 2);
		return FALSE;
	}
    else if ((type == C && type ==  F) && !check_on_values(path))//this to check on values
    {
        error_handling("Values" , 2);
		return FALSE;
    }
	data->texture[(int)type] = path;//now i am already have the path
	data->count_of_elements++;
	return TRUE;
}



// this fun is for searching for the something i needs and it starts with
// NO//SO//WE//EA//F//c
int	extract_data(t_config *data, char *line)
{
	char *trim = ft_strtrim(line, "\n \t");
		// now i have a full line full of data
	if (ft_strncmp(trim, "NO ", 3) == 0)
	{
		if (!add_to_data(data,trim,NO , 3))
			return FALSE;
	}
	else if (ft_strncmp(trim, "SO ", 3) == 0)
	{
	}
	else if (ft_strncmp(trim, "WE ", 3) == 0)
	{
	}
	else if (ft_strncmp(trim, "EA ", 3) == 0)
	{
	}
	else if (ft_strncmp(trim, "F ", 2) == 0)
	{
	}
	else if (ft_strncmp(trim, "C ", 2) == 0)
	{
	}
	else
	{
		error_handling("Invalid identifier");
		return (FALSE);
	}
	if (have_duplicate() || ||)
		return (FALSE);
	return (TRUE);
}