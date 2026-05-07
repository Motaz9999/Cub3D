#ifndef CUB3D_H
# define CUB3D_H
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
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

// errors
int			error_handling(char *context, int exit_code);
// clean data and structs and free them
void		clean_data(t_config *data);

// Init structs
void		init_game(t_game *game);
void		init_map(t_map *map);
void		init_config(t_config *config);

// parsing
t_config	*parse_file(char *file_name);
int			parse_map(t_config *data);
int			check_extension(char *path, char *ext);
void		print_map(t_map *map);
// make map
char		**make_map(int fd, char *first_row, char *set);
// remake map
char		**remake_map(t_map *map);
// algorithm to check of map

// checks for paths and values
int			check_on_path(char *path);
int			check_on_value(char *value);
// data
int			extract_data(t_config *data, char *line);
#endif