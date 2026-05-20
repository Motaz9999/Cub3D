/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 11:25:19 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/20 13:29:46 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this fun is for setting the window the first time
static int	init_window(t_game *game)
{
	game->mlx_lib->win = mlx_new_window(game->mlx_lib->mlx, WIDTH_OF_WIN,
			HIGHT_OF_WIN, "Cub3D");
	if (!game->mlx_lib->win)
	{
		mlx_destroy_display(game->mlx_lib->mlx);
		free(game->mlx_lib->mlx);
		free(game->mlx_lib);
		game->mlx_lib = NULL;
		return (error_handling("error in mlx_new_window", (int)FALSE));
	}
	return (TRUE);
}

// this fun is for setting (img pointer) i will use to put imgs in it then print it in window
static int	init_image(t_game *game)
{
	game->mlx_lib->img = mlx_new_image(game->mlx_lib->mlx, WIDTH_OF_WIN,
			HIGHT_OF_WIN);
	if (!game->mlx_lib->img)
	{
		mlx_destroy_window(game->mlx_lib->mlx, game->mlx_lib->win);
		mlx_destroy_display(game->mlx_lib->mlx);
		free(game->mlx_lib->mlx);
		free(game->mlx_lib);
		game->mlx_lib = NULL;
		return (error_handling("error in mlx_new_image", (int)FALSE));
	}
	game->mlx_lib->addr = mlx_get_data_addr(game->mlx_lib->img, &game->mlx_lib->bpp,
			&game->mlx_lib->line_len, &game->mlx_lib->endian);
	return (TRUE);
}

//this fun malloc a whole stuct for the mlx lib
//each element in this struct is for something
int	setup_mlx(t_game *game)
{
	game->mlx_lib = malloc(sizeof(t_mlx));
	if (!game->mlx_lib)
		return (error_handling("error in mlx lib", (int)FALSE));
	init_mlx_lib(game->mlx_lib);
	game->mlx_lib->mlx = mlx_init();//link to lib
	if (!game->mlx_lib->mlx)
	{
		free(game->mlx_lib);
		game->mlx_lib = NULL;
		return (error_handling("error in mlx_init", (int)FALSE));
	}
	if (!init_window(game))
		return (FALSE);
	if (!init_image(game))
		return (FALSE);
	return (TRUE);
}
