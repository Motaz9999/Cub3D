/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy_free_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:30:34 by moodeh            #+#    #+#             */
/*   Updated: 2026/02/27 06:59:24 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*get_next(void *node, size_t offset)
{
	return (*(void **)((char *)node + offset));
}

static void	set_next(void *node, size_t offset, void *value)
{
	*(void **)((char *)node + offset) = value;
}

void	*ft_lstcopy_generic(void *head, t_lst_ops ops)
{
	void	*new_head;
	void	*prev;
	void	*new_node;
	void	*current;

	new_head = NULL;
	prev = NULL;
	current = head;
	while (current)
	{
		new_node = ops.dup(current);
		if (!new_node)
		{
			ft_lstfree_generic(new_head, ops);
			return (NULL);
		}
		if (!new_head)
			new_head = new_node;
		if (prev)
			set_next(prev, ops.next_offset, new_node);
		prev = new_node;
		current = get_next(current, ops.next_offset);
	}
	return (new_head);
}

void	ft_lstfree_generic(void *head, t_lst_ops ops)
{
	void	*current;
	void	*next;

	current = head;
	while (current)
	{
		next = get_next(current, ops.next_offset);
		if (ops.del)
			ops.del(current);
		free(current);
		current = next;
	}
}
