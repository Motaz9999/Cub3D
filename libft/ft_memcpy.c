/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:40:14 by moodeh            #+#    #+#             */
/*   Updated: 2025/08/19 14:42:45 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, void const *src, size_t size)
{
	unsigned char	*srcptr;
	unsigned char	*destptr;

	srcptr = (unsigned char *)src;
	destptr = (unsigned char *)dest;
	while (size > 0)
	{
		*destptr = *srcptr;
		destptr++;
		srcptr++;
		size--;
	}
	return (dest);
}
