/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:08:05 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/16 09:58:20 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// (this is flood fill using BFS & Queue)
// malloc(sizeof(t_point) * hight * max_width);
// cuse i want to store points locations in the whole map if it require to
// the queue will have an head and tail
// this array of points will record queues
// head is the first element in the queue
// when u add(push) an element u add on tail and the head will still remain
// and when u delete(pop) u use the first element the tail adds (head)
// then head goes to the next 1 and by this we make queue
// X is the line and y is the the element in the line

static t_point	add_point(t_point point, int x, int y)
{
	point.x = x;
	point.y = y;
	return (point);
}

// ok this fun job is adding the right neighbors
// but check on them before adding them like are they are valid
// like if the row have 4zeros 0000 and the last zero try to go to then next its not valid
// or if the zero have a neighbors of space this is not valid
// after all and adding zeros into the queue
// we return to the main fun
// so the check are
// (1 , 0) up  , (-1 ,0 ) down ,  (0 , 1) right , (0 , -1) right left
// so we make them as double arrays and these arrays
static int	check_on_4_dirs(t_point *queue, char **map, t_point *point, int *tail,
		t_map *map_data)
{
	int	i;
	int	next_x;
	int	next_y;

	int dx[] = {1, -1, 0, 0}; // first the up and down
	int dy[] = {0, 0, 1, -1}; // the right then left
	i = 0;
	while (i < 4) // sec step is to check on the map chars
	{
		next_x = point->x + dx[i];
		next_y = point->y + dy[i];
		if (next_x < 0 || next_x >= map_data->map_hight || next_y < 0
			|| next_y >= map_data->map_width)
		{
			return (FALSE);
		}
		if (map[next_x][next_y] == ' ')
			return (FALSE);
		if (map[next_x][next_y] == '1')
		{
			i++;
			continue ;
		}
		if (map[next_x][next_y] == '0')
		{
			map[next_x][next_y] = '1';
			inqueue(queue, tail, add_point(*point, dx[i], dy[i]));
		}
		i++;
	}
	return (TRUE);
}

// what will be visited are the one is with V
// and if u have void it must me srounded by 1s
// and if zero touch void the map is not valid
// and if player touch
int	flood_fill(char **map, t_map *map_data)
{
	t_point	*queue;
	int		head_index;
	int		tail_index;
	t_point	point;


	queue = malloc(sizeof(t_point) * (map_data->map_hight
				* map_data->map_width));
	init_queue(queue, (map_data->map_hight * map_data->map_width) ,&tail_index , &head_index);
	point.x = map_data->player_loc->x;
	point.y = map_data->player_loc->y;
	map[point.x][point.y] = '1'; // already visited
	inqueue(queue, &tail_index, point);
	while (!is_queue_empty(head_index, tail_index))
	{
		point = dequeue(queue, &head_index);
		if (!check_on_4_dirs(queue, map, &point, &tail_index, map_data))
		{
			free(queue);
			return (error_handling("Invalid map : Leak detected", (int)FALSE));
		}
	}
	free(queue);
	return (TRUE);
}
