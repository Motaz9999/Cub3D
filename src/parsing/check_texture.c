/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 07:26:39 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/08 07:30:23 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// this fun is just for seeing if i have all the real texture and all works fine
int	check_texture(t_config *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (i < 4)
	{
		fd = open(data->texture[i], O_RDONLY);
		if (fd == -1)
			return (error_handling("texture file not readble", (int)FALSE));
		close(fd);
		i++;
	}
	return (TRUE);
}
