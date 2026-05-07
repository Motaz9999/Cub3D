/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:07:21 by moodeh            #+#    #+#             */
/*   Updated: 2025/12/23 05:40:37 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_all(void *first, ...)
{
	void	*ptr;
	va_list	args_to_free;

	if (first == NULL)
		return ;
	va_start(args_to_free, first);
	ptr = first;
	while (ptr != NULL)
	{
		free(ptr);
		ptr = va_arg(args_to_free, void *);
	}
	va_end(args_to_free);
}

void	ft_free_all2(void **first, ...)
{
	void	**ptr;
	int		i;
	va_list	args_to_free;

	if (first == NULL)
		return ;
	va_start(args_to_free, first);
	ptr = first;
	while (ptr != NULL)
	{
		i = 0;
		while (ptr[i] != NULL)
		{
			free(ptr[i]);
			i++;
		}
		free(ptr);
		ptr = va_arg(args_to_free, void **);
	}
	va_end(args_to_free);
}
