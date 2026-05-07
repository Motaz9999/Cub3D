/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:28:57 by moodeh            #+#    #+#             */
/*   Updated: 2025/08/19 14:42:40 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*pstr;

	pstr = (unsigned char *) str;
	while (n > 0)
	{
		if (*pstr == (unsigned char)c)
		{
			return (pstr);
		}
		n--;
		pstr++;
	}
	return (NULL);
}
