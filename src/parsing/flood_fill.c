/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:08:05 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/04 20:15:33 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_fill(t_fill *fill, char **map, t_map *map_data)
{
	fill->queue = NULL;
	fill->map = map;
	fill->tail = NULL;
	fill->map_data = map_data;
}

static void	setup_queue(t_fill *fill, int *head, int *tail, t_point *point)
{
	init_queue(fill->queue, fill->map_data->map_hight
		* fill->map_data->map_width, tail, head);
	fill->tail = tail;
	point->x = fill->map_data->player_loc->x;
	point->y = fill->map_data->player_loc->y;
	fill->map[point->y][point->x] = '1';
	inqueue(fill->queue, tail, *point);
}

static int	fill_error(t_fill *fill)
{
	free(fill->queue);
	return (error_handling("Invalid map : Leak detected",
			(int)FALSE));
}

int	flood_fill(char **map, t_map *map_data)
{
	t_fill	fill;
	int		head_index;
	int		tail_index;
	t_point	point;

	init_fill(&fill, map, map_data);
	fill.queue = malloc(sizeof(t_point) * (map_data->map_hight
				* map_data->map_width));
	if (!fill.queue)
		return (FALSE);
	setup_queue(&fill, &head_index, &tail_index, &point);
	while (!is_queue_empty(head_index, tail_index))
	{
		point = dequeue(fill.queue, &head_index);
		if (!check_on_4_dirs(&fill, &point))
			return (fill_error(&fill));
	}
	free(fill.queue);
	return (TRUE);
}
