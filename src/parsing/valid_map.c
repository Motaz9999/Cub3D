/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 10:22:26 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/08 08:14:44 by moodeh           ###   ########.fr       */
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
		line_len = strlen(map[y]);
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

int	valid_map(t_map *map_data)
{
	if (!check_outer_edges(map_data->map, map_data->map_hight)
		|| !bfs(map_data->map, map_data->map_hight, map_data->map_width))
		return (FALSE);
	return (TRUE);
}