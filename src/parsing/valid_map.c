/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 10:22:26 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/10 21:17:25 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player_char(char c)
{
	if (c == 'S' || c == 'E' || c == 'W' || c == 'N')
		return (TRUE);
	return (FALSE);
}

static int	check_player_at(t_map *map_data, int i, int j, int *count)
{
	if (!is_player_char(map_data->map[i][j]))
		return (TRUE);
	map_data->player_loc->x = j;
	map_data->player_loc->y = i;
	map_data->player_face = map_data->map[i][j];
	(*count)++;
	if (*count > 1)
		return (error_handling("more than 1 player", (int)FALSE));
	return (TRUE);
}

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
			if (!check_player_at(map_data, i, j, &count))
				return (FALSE);
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
	char	**new_map;

	if (!find_player_and_check(map_data))
		return (FALSE);
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
