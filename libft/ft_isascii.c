/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:06:28 by moodeh            #+#    #+#             */
/*   Updated: 2025/08/09 15:30:27 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_isascii: Checks whether c is a 7-bit unsigned char value that fits into the ASCII character set.
*/
int	ft_isascii(int asc)
{
	if (asc >= 0 && asc <= 127)
		return (1);
	return (0);
}
