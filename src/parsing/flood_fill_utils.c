/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 20:12:42 by samarnah          #+#    #+#             */
/*   Updated: 2026/07/04 20:15:53 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	add_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_point	get_next_point(t_point *point, int index)
{
	t_point	next;

	next.x = point->x;
	next.y = point->y;
	if (index == 0)
		next.y++;
	else if (index == 1)
		next.y--;
	else if (index == 2)
		next.x++;
	else
		next.x--;
	return (next);
}

int	is_outside_map(t_fill *fill, t_point next)
{
	if (next.y < 0 || next.y >= fill->map_data->map_hight)
		return (TRUE);
	if (next.x < 0 || next.x >= fill->map_data->map_width)
		return (TRUE);
	return (FALSE);
}

int	check_next_point(t_fill *fill, t_point next)
{
	if (is_outside_map(fill, next))
		return (FALSE);
	if (fill->map[next.y][next.x] == ' ')
		return (FALSE);
	if (fill->map[next.y][next.x] == '0')
	{
		fill->map[next.y][next.x] = '1';
		inqueue(fill->queue, fill->tail, next);
	}
	return (TRUE);
}

int	check_on_4_dirs(t_fill *fill, t_point *point)
{
	int		i;
	t_point	next;

	i = 0;
	while (i < 4)
	{
		next = get_next_point(point, i);
		if (!check_next_point(fill, next))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
