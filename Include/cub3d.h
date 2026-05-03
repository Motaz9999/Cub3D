#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
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
// parsing
t_config	*parse_file(char *file_name);
int check_extension(char *path, char *ext);
//checks for paths and values 
int check_on_path(char *path);
int check_on_value(char *value);
#endif