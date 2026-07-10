/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 21:16:33 by samarnah          #+#    #+#             */
/*   Updated: 2026/07/10 21:17:48 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
