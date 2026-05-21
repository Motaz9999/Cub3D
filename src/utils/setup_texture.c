/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:37:44 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/21 16:36:11 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_on_all_texture(t_texture *texture)
{
	if (!texture->no_texture || !texture->so_texture || !texture->we_texture
		|| !texture->ea_texture)
	{
		return (error_handling("failed to load texture from path", (int)FALSE));
	}
	if (texture->c_color == -1 || texture->f_color == -1)
	{
		return (error_handling("failed to convert color", (int)FALSE));
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
static int	convert_to_color(char *data)
{
	char	**nums;
	int		ret;
	int		alpha;
	int		r;
	int		g;
	int		b;

	nums = ft_split(data, ',');
	if (nums == NULL)
		return (-1);
	alpha = (int)ALPHA_COLOR;
	ret = 0;
	r = ft_atoi(nums[0]); // red color
	g = ft_atoi(nums[1]); // green color
	b = ft_atoi(nums[2]); // blue color
	if ((alpha > 255 || alpha < 0) || (r > 255 || r < 0) || (g > 255 || g < 0)
		|| (b > 255 || b < 0))
	{
		ft_free_all2((void **)nums, NULL);
		return (-1);
	}
	ret = (alpha << 24) | (r << 16) | (g << 8) | b;
	ft_free_all2((void **)nums, NULL);
	return (ret);
}

// this fun for setup the texture to use them later in the img draw
static int	load_texture(void *mlx, t_texture *texture, t_config *data)
{
	int	w;
	int	h;

	texture->no_texture = mlx_xpm_file_to_image(mlx, data->texture[(int)NO], &w,
			&h);
	texture->so_texture = mlx_xpm_file_to_image(mlx, data->texture[(int)SO], &w,
			&h);
	texture->we_texture = mlx_xpm_file_to_image(mlx, data->texture[(int)WE], &w,
			&h);
	texture->ea_texture = mlx_xpm_file_to_image(mlx, data->texture[(int)EA], &w,
			&h);
	texture->c_color = convert_to_color(data->texture[(int)C]);
	texture->f_color = convert_to_color(data->texture[(int)F]);
	if (!check_on_all_texture(texture))
		return (FALSE);
	return (TRUE);
}

// i have 4 texture to load and there are in order
//	NO,
//	SO,
//	WE,
//	EA,
//	C,	F not texture but i need them as 1 number 32 bit (use bitwise ops to do it )
void	setup_texture(t_game *game)
{
	game->loaded_texture = malloc(sizeof(t_texture));
	init_texture(game->loaded_texture);
	if (!load_texture(game->mlx_lib->mlx, game->loaded_texture,
			game->config_file_data))
	{
		clean_texture(game->mlx_lib->mlx, game->loaded_texture);
		game->loaded_texture = NULL;
		return ;
	}
}
