/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 22:59:19 by samarnah          #+#    #+#             */
/*   Updated: 2026/07/10 23:03:27 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_texture_2d(void *mlx, void *image, int **texture)
{
	if (image != NULL)
		mlx_destroy_image(mlx, image);
	if (texture != NULL)
		ft_free_all2((void **)texture, NULL);
}

static int	fill_texture_row(int *row, char *addr, int image_data[3],
		int row_index)
{
	char	*pixel;
	int		j;

	j = 0;
	while (j < image_data[0])
	{
		pixel = addr + row_index * image_data[2]
			+ j * (image_data[1] / 8);
		row[j] = *(unsigned int *)pixel;
		j++;
	}
	return (TRUE);
}

static int	fill_texture_array(int **texture, char *addr,
		int image_data[3], int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		texture[i] = malloc(sizeof(int) * image_data[0]);
		if (texture[i] == NULL)
			return (FALSE);
		fill_texture_row(texture[i], addr, image_data, i);
		i++;
	}
	texture[height] = NULL;
	return (TRUE);
}

// this fun its make the texture into array of colors 
// like imagin the whole texture pix of an array of 64x64 
// and this array have on pixle color
// the height here represent how many rows i have in the img
//->rows and the width is how many pixels are in the 1 row
// so what we doing here is to save each pixel in this array of pixels
// to move inside a rows we use  (j * (bpp / 8))
//	->the bpp is any type of bitrate img
// and to move rows itself we use (i *line_len)
// and both are inside adder
static void	*load_texture_image(void *mlx, char *file_name,
		int *width, int *height)
{
	void	*image;

	image = mlx_xpm_file_to_image(mlx, file_name, width, height);
	if (image == NULL)
		error_handling("failed to load texture", (int)FALSE);
	return (image);
}

static int	**make_texture_2d(void *mlx, char *file_name, int *width,
		int *height)
{
	void	*image;
	char	*addr;
	int		image_data[3];
	int		**texture;

	image = load_texture_image(mlx, file_name, width, height);
	if (image == NULL)
		return (NULL);
	addr = mlx_get_data_addr(image, &image_data[1],
			&image_data[2], &image_data[0]);
	image_data[0] = *width;
	texture = ft_calloc(*height + 1, sizeof(int *));
	if (texture == NULL
		|| !fill_texture_array(texture, addr, image_data, *height))
	{
		free_texture_2d(mlx, image, texture);
		return (NULL);
	}
	mlx_destroy_image(mlx, image);
	return (texture);
}
