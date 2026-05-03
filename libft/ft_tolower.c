/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:59:33 by moodeh            #+#    #+#             */
/*   Updated: 2025/08/19 14:44:02 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_tolower: Converts the letter c to lower case, if possible.
*/
int	ft_tolower(int ch)
{
	if (ch >= 65 && ch <= 90)
	{
		ch += 32;
	}
	return (ch);
}
