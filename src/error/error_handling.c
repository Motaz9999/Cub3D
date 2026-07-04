/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 22:18:27 by moodeh            #+#    #+#             */
/*   Updated: 2026/07/04 19:03:49 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_handling(char *context, int exit_code)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(context, 2);
	ft_putstr_fd("\n", 2);
	return (exit_code);
}
