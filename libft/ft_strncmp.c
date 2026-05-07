/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:16:51 by moodeh            #+#    #+#             */
/*   Updated: 2025/08/19 14:43:36 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	unsigned char	*pts1;
	unsigned char	*pts2;
	size_t			i;

	pts1 = (unsigned char *)s1;
	pts2 = (unsigned char *)s2;
	i = 0;
	while (size > i)
	{
		if (pts1[i] != pts2[i])
		{
			return (pts1[i] - pts2[i]);
		}
		if (pts1[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
