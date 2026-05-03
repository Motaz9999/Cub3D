/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_on_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moodeh <moodeh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 22:36:17 by moodeh            #+#    #+#             */
/*   Updated: 2026/05/04 01:57:28 by moodeh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


//this fun is to check on the whole path
//and if it real path and if i can use it
//first must check if the end of it is xmp
int check_on_path(char *path)
{
    if (!check_extension(path , ".xpm"))
    {
        error_handling("extension in texture file" , 2);
        return FALSE;
    }
}
