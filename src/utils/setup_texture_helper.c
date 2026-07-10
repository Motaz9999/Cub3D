/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_texture_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 22:58:34 by samarnah          #+#    #+#             */
/*   Updated: 2026/07/10 23:56:27 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	color_is_valid(int color[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (color[i] < 0 || color[i] > 255)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

// this fun have 123,123,123
// so it have 3 numbers have , between them
// and all together must be 32bit color
// using bitwise shifting
// Color = (A << 24) | (R << 16) | (G << 8) | B
// each number is 8bit len
// from 0-7 this is blue color
// 8-15 green
// 16-23 red
// 24-31 alpha -> how deep the color are
// so we use left shifting and or opr so it all have a whole some value
// so this mean that i use the whole number to make one color
// this color is 32bit and if u convert into hexa u will find it
// aw each element start from bit to bit and we must be sure about colors
// this like i insert each num in
// its right place in the 32bit  like the 32-24 bits are for alpha a...
int	convert_to_color(char *data)
{
	char	**nums;
	int		color[4];
	int		ret;

	nums = ft_split(data, ',');
	if (nums == NULL)
		return (-1);
	color[0] = (int)ALPHA_COLOR;
	color[1] = ft_atoi(nums[0]);
	color[2] = ft_atoi(nums[1]);
	color[3] = ft_atoi(nums[2]);
	if (!color_is_valid(color))
	{
		ft_free_all2((void **)nums, NULL);
		return (-1);
	}
	ret = (color[0] << 24) | (color[1] << 16);
	ret |= (color[2] << 8) | color[3];
	ft_free_all2((void **)nums, NULL);
	return (ret);
}
