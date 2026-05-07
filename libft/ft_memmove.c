/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:40:13 by moodeh            #+#    #+#             */
/*   Updated: 2025/08/19 14:42:49 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptdest;
	unsigned char	*ptsrc;

	ptdest = (unsigned char *)dest;
	ptsrc = (unsigned char *)src;
	if (src < dest)
	{
		ptdest += n - 1;
		ptsrc += n - 1;
		while (n > 0)
		{
			*ptdest = *ptsrc;
			ptdest--;
			ptsrc--;
			n--;
		}
	}
	else
	{
		dest = ft_memcpy(dest, src, n);
	}
	return (dest);
}
