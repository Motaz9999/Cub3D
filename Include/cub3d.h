/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 19:32:14 by samarnah          #+#    #+#             */
/*   Updated: 2026/07/04 19:32:51 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "struct.h"
# include <error.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# define TRUE 1
# define FALSE 0

# define TEXTURE 64.0

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_RIGHT 65363
# define KEY_LEFT 65361

# define BLOCK 8

# define HITBOX 0.15

# define MOVE_SPEED 0.03

# define ROT_SPEED 0.03

# define FOV_DIG 66.8

# define WIDTH_OF_WIN 800
# define HIGHT_OF_WIN 600

# define ALPHA_COLOR 120

// errors
int			error_handling(char *context, int exit_code);
// clean data and structs and free them
void		clean_data(t_config *data);
void		clean_mlx_data(t_mlx *mlx_lib);
void		clean_texture(void *mlx_ptr, t_texture *texture);
void		clean_game(t_game *game);

// Init structs
void		init_game(t_game *game);
void		init_map(t_map *map);
void		init_config(t_config *config);
void		init_mlx_lib(t_mlx *mlx_lib);
void		init_texture(t_texture *texture);
void		init_key(t_key *keys);
void		init_player(t_player *player);

// mlx
int			setup_mlx(t_game *game);
void		put_pixel_to_img_buffer(t_mlx *mlx_lib, int x, int y, int color);
// parsing
t_config	*parse_file(char *file_name);
int			parse_map(t_config *data);
int			check_extension(char *path, char *ext);
void		print_map(t_map *map);

// texture
int			check_texture(t_config *data);
void		setup_texture(t_game *game);

// make map
char		**make_map(int fd, char *first_row, char *set);

// remake map
char		**remake_map(t_map *map);

// algorithm to check of map
// queue
void		init_queue(t_point *queue, int capacity, int *tail_index,
				int *head_index);
t_point		dequeue(t_point *queue, int *head);
void		inqueue(t_point *queue, int *tail, t_point new_point);
int			is_queue_empty(int head, int tail);
int			flood_fill(char **map, t_map *map_data);

// checks for paths and values
int			check_on_path(char *path);
int			check_on_value(char *value);

// data
int			extract_data(t_config *data, char *line);
int			valid_map(t_map *map_data);

// render
int			render(void *game_void);
void		render_as_3d(t_game *game);
void		render_a_slice(t_game *game, t_ray *ray, double ray_len,
				int i_in_width, double ray_dir_x, double ray_dir_y);

// hooks
int			setup_hooks(t_game *game);
// close game
int			close_game(void *game_void);

// player
int			setup_player(t_game *game);
// movement
void		handle_movement(t_game *game);
void		move_backward(t_game *game);
void		move_forward(t_game *game);
void		strafe_left(t_game *game);
void		strafe_right(t_game *game);
// 2d map
void		draw2d_map(t_game *game);
#endif