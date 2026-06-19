/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:37:44 by moodeh            #+#    #+#             */
/*   Updated: 2026/06/19 11:17:33 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_on_all_texture(t_texture *texture)
{
	if (!texture->no_texture || !texture->so_texture || !texture->we_texture
		|| !texture->ea_texture)
	{
		return (error_handling("failed to load texture as 2d array",
				(int)FALSE));
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

static void	free_texture_2d(void *mlx, void *image, int **texture)
{
	if (image != NULL)
		mlx_destroy_image(mlx, image);
	if (texture != NULL)
		ft_free_all2((void **)texture, NULL);
}

// this fun its make the texture into array of colors like imagin the whole texture pix of an array of 64x64 and this array have on pixle color
// the height here represent how many rows i have in the img
//->rows and the width is how many pixels are in the 1 row
// so what we doing here is to save each pixel in this array of pixels
// to move inside a rows we use  (j * (bpp / 8))
//	->the bpp is any type of bitrate img
// and to move rows itself we use (i *line_len)
// and both are inside adder
static int	**make_texture_2d(void *mlx, char *flie_name, int *width,
		int *height)
{
	void			*texture;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				**array_of_texture;
	char			*pixel;
	int				i;
	int				j;
	texture = mlx_xpm_file_to_image(mlx, flie_name, width, height);
	if (texture == NULL)
	{
		error_handling("failed to load texture", (int)FALSE);
		return (NULL);
	}
	addr = mlx_get_data_addr(texture, &bpp, &line_len, &endian);
	array_of_texture = ft_calloc((*height) + 1, sizeof(int *));
	if (array_of_texture == NULL)
	{
		free_texture_2d(mlx, texture, NULL);
		return (NULL);
	}
	i = 0;
	while (i < (*height))
	{
		array_of_texture[i] = malloc(sizeof(int) * (*width));
		if (array_of_texture[i] == NULL)
		{
			free_texture_2d(mlx, texture, array_of_texture);
			return (NULL);
		}
		j = 0;
		while (j < (*width))
		{
			pixel = addr + (i * line_len + j * (bpp / 8));
			array_of_texture[i][j] = *(unsigned int *)pixel;
			j++;
		}
		i++;
	}
	array_of_texture[*height] = NULL;
	mlx_destroy_image(mlx, texture); // we dont use this img anymore
	return (array_of_texture);
}

// this fun for setup the texture to use them later in the img draw
static int	load_texture(void *mlx, t_texture *texture, t_config *data)
{
	texture->no_texture = make_texture_2d(mlx, data->texture[(int)NO],
			&texture->width, &texture->hight);
	texture->so_texture = make_texture_2d(mlx, data->texture[(int)SO],
			&texture->width, &texture->hight);
	texture->we_texture = make_texture_2d(mlx, data->texture[(int)WE],
			&texture->width, &texture->hight);
	texture->ea_texture = make_texture_2d(mlx, data->texture[(int)EA],
			&texture->width, &texture->hight);
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
