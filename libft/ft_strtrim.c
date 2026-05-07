/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:23:52 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/03 22:00:36 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_inset(char s, char *set)
{
	int	con;

	con = 0;
	while (*set != '\0')
	{
		if (*set == s)
		{
			con = 1;
			break ;
		}
		set++;
	}
	return (con);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	char		*ptr;
	int			start;
	int			end;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] != '\0' && ft_is_inset(s1[start], (char *)set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && ft_is_inset(s1[end], (char *)set))
		end--;
	str = malloc(sizeof(char) * ((end - start) + 2));
	if (!str)
		return (NULL);
	ptr = str;
	while (start <= end)
	{
		*str = s1[start++];
		str++;
	}
	*str = '\0';
	return (ptr);
}
