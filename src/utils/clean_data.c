/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 02:50:38 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/02 02:55:57 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//this fun is for clean the config data file 
void	clean_data(t_config *data)
{
	if (data == NULL)
		return ;
	if (data->fd != -1)
		close(data->fd);
	if (data->floor_and_ceiling != NULL)
		clean_t_c_f_data(data->floor_and_ceiling);
	if (data->map != NULL)
		clean_map(data->map);
	if (data->texture != NULL)
		clean_texture(data->texture);
	free(data);
}
