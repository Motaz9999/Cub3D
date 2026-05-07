/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:29:30 by moodeh            #+#    #+#             */
/*   Updated: 2025/08/19 14:53:35 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*loca;
	size_t			i;

	if (nmemb == 0 || size == 0)
	{
		return (malloc(1));
	}
	if (nmemb != 0 && nmemb > (size_t)(-1) / size)
	{
		return (NULL);
	}
	i = size * nmemb;
	loca = malloc(i);
	if (loca == NULL)
	{
		return (NULL);
	}
	while (i > 0)
	{
		loca[i - 1] = 0;
		i--;
	}
	return (loca);
}
