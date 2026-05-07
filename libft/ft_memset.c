/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:20:39 by moodeh            #+#    #+#             */
/*   Updated: 2025/08/19 14:42:52 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int value, size_t num)
{
	unsigned char	*sptr;

	sptr = (unsigned char *)s;
	while (num > 0)
	{
		*sptr = (unsigned char)value;
		sptr++;
		num--;
	}
	return (s);
}
