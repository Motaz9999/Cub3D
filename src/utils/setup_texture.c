/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 16:37:44 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/10 23:46:33 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* meanings:
image_data[0] = width;
image_data[1] = bpp;
image_data[2] = line length;*/
static int	check_on_all_texture(t_texture *texture)
{
	if (!texture->no_texture || !texture->so_texture
		|| !texture->we_texture || !texture->ea_texture)
	{
		return (error_handling("failed to load texture as 2d array",
				(int)FALSE));
	}
	if (texture->c_color == -1 || texture->f_color == -1)
		return (error_handling("failed to convert color", (int)FALSE));
	return (TRUE);
}

// this fun for setup the texture to use them later in the img draw
// i have 4 texture to load and there are in order
//	NO,
//	SO,
//	WE,
//	EA,
//	C,	F not texture but i need them as 1 number 32 bit 
// (use bitwise ops to do it )
int	load_texture(void *mlx, t_texture *texture, t_config *data)
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
