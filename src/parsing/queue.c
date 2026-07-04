/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 08:31:27 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/04 19:19:38 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// add (enqueue) add to back , delete(dequeue) remove from the front, free queue
// the queue can be linked list 
// or it can be array but here we want to use it as array

void	init_queue(t_point *queue, int capacity, int *tail_index,
		int *head_index)
{
	int	i;

	i = 0;
	*tail_index = 0;
	*head_index = 0;
	while (i < capacity)
	{
		queue[i].x = 0;
		queue[i].y = 0;
		i++;
	}
}

// put in the queue
void	inqueue(t_point *queue, int *tail, t_point new_point)
{
	queue[*tail] = new_point;
	(*tail)++;
}

// remove from the queue
t_point	dequeue(t_point *queue, int *head)
{
	t_point	temp;

	temp = queue[*head];
	(*head)++;
	return (temp);
}

int	is_queue_empty(int head, int tail)
{
	if (head == tail)
		return (1);
	return (0);
}
