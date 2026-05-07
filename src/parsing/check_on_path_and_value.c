/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_on_path_and_value.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 22:36:17 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/07 09:39:30 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_on_number_range(char *str)
{
	int	color;

	color = ft_atoi(str);
	if (color < 0 || color > 255)
	{
		error_handling("RGB values must be between 0 and 255", 2);
		return (FALSE);
	}
	return (TRUE);
}

static int	is_valid_rgb_number(char *str)
{
	int	j;

	j = 0;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	if (!str[j] || str[j] == '\n')
		return (error_handling("Invalid RGB value format", (int)FALSE));
	while (str[j] && str[j] != '\n')
	{
		if (!ft_isdigit(str[j]) && str[j] != ' ' && str[j] != '\t')
			return (error_handling("RGB values must be digits", (int)FALSE));
		j++;
	}
	if (!check_on_number_range(str))
		return (FALSE);
	return (TRUE);
}

// this fun have a list of numbers [255, 1, 23] and checks on them
static int	validate_rgb_array(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (!is_valid_rgb_number(rgb[i]))
			return (FALSE);
		i++;
	}
	if (i != 3)
		return (error_handling("RGB must contain exactly 3 values",
				(int)FALSE));
	return (TRUE);
}

// this fun is for checking on values like (255 , 0 ,231)
int	check_on_value(char *value)
{
	char	**rgb;
	char	*trimmed;

	trimmed = ft_strtrim(value, " \t\n");
	if (!trimmed)
		return (FALSE);
	rgb = ft_split(trimmed, ',');
	free(trimmed);
	if (!rgb)
		return (FALSE);
	if (!validate_rgb_array(rgb))
	{
		ft_free_all2((void **)rgb, NULL);
		return (FALSE);
	}
	ft_free_all2((void **)rgb, NULL);
	return (TRUE);
}

// this fun is to check on the whole path
// and if it real path and if i can use it
// first must check if the end of it is xmp
int	check_on_path(char *path)
{
	int	fd;

	if (!check_extension(path, ".xpm"))
		return (error_handling("extension in texture file", (int)FALSE));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (error_handling("cant open texture file", (int)FALSE));
	close(fd);
	return (TRUE);
}
