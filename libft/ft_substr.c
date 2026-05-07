/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:01:45 by moodeh            #+#    #+#             */
/*   Updated: 2025/08/19 14:43:57 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	char	*ptr;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	s += start;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sub = malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	ptr = sub;
	while (*s != '\0' && len > 0)
	{
		*sub = *s;
		s++;
		sub++;
		len--;
	}
	*sub = '\0';
	return (ptr);
}
