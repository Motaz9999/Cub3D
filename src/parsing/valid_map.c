/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 10:22:26 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/14 17:21:29 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this fun is to be sure no wrong on edges soo bfs algo works perfect
// y == 0 first line ,, y == height-1  last line
// x == 0 first element in line ,, x ==line_len - 1 last element in the line
// so this is initial check
int	check_outer_edges(char **map, int height)
{
	int	x;
	int	y;
	int	line_len;

	y = 0;
	while (y < height)
	{
		line_len = ft_strlen(map[y]);
		x = 0;
		while (x < line_len)
		{
			if (y == 0 || y == height - 1 || x == 0 || x == line_len - 1)
			{
				if (map[y][x] != '1' && map[y][x] != ' ')
					return (error_handling("map edge", (int)FALSE));
			}
			x++;
		}
		y++;
	}
	return (TRUE);
}

// this fun is for copying the whole map
char	**copy_map(char **map_2d, int n)
{
	int		i;
	char	**copy_map;

	i = 0;
	copy_map = malloc((n + 1) * sizeof(char *));
	if (!copy_map)
		return (NULL);
	while (i < n)
	{
		copy_map[i] = ft_strdup(map_2d[i]);
		if (!copy_map[i])
		{
			ft_free_all2((void **)copy_map, NULL);
			return (NULL);
		}
		i++;
	}
	copy_map[n] = NULL;
	return (copy_map);
}

// this fun is for search for player loc and check if there is more than 1 player
// true mean that i have the player loc
// false mean that i have more than one or none
// i is the row
int	find_player_and_check(t_map *map_data)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (map_data->map[i] != NULL)
	{
		j = 0;
		while (map_data->map[i][j] != '\0')
		{
			if (map_data->map[i][j] == 'S' || map_data->map[i][j] == 'E'
				|| map_data->map[i][j] == 'W' || map_data->map[i][j] == 'N')
			{
				map_data->player_loc->x = j;
				map_data->player_loc->y = i;
				map_data->player_face = map_data->map[i][j];
				count++;
			}
			if (count > 1)
				return (error_handling("more than 1 player", (int)FALSE));
			j++;
		}
		i++;
	}
	if (count == 0)
		return (error_handling("no player found", (int)FALSE));
	return (TRUE);
}

int	valid_map(t_map *map_data)
{
	char **new_map;
	if (!find_player_and_check(map_data))
	{
		return (FALSE);
	}
	new_map = copy_map(map_data->map, map_data->map_hight);
	if (!new_map)
		return (FALSE);
	if (!check_outer_edges(map_data->map, map_data->map_hight)
		|| !flood_fill(new_map, map_data))

	{
		ft_free_all2((void **)new_map, NULL);
		return (FALSE);
	}
	ft_free_all2((void **)new_map, NULL);
	return (TRUE);
}