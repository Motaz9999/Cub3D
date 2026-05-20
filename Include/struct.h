#ifndef STRUCT_H
# define STRUCT_H

// for queue and player
typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

// use when i make the raycasting
typedef struct s_player
{
	float		x;
	float		y;
	float		z;
}				t_player;

typedef struct s_map
{
	char **map;     // the hole map
	char *map_char; // allowed chars
	int map_hight;  // the hight of the whole map
	int			map_width;
	t_point		*player_loc;
	char		player_face;
	// u must also add the player loc
}				t_map;

// from 0-5 -> 6 elements
typedef enum e_type_of_text
{
	NO,
	SO,
	WE,
	EA,
	C,
	F
}				t_type_of_text;

typedef struct s_config
{
	int			fd;
	int			count_of_elements;
	char *texture[6]; // texture path checks NO,SO,WE,EA,C,F(see the enum to know what each index mean)
	char		*save_line_map;
	t_map		*map_data;
}				t_config;

typedef struct s_mlx
{
	void *mlx;    // connection to display
	void *win;    // the window
	void *img;    // the image buffer
	char *addr;   // raw pixel array inside the image
	int bpp;      // bits per pixel
	int line_len; // bytes per row
	int endian;   // byte order
}				t_mlx;

typedef struct s_game
{
	t_config	*config_file_data;
	t_player	*player;
	t_mlx		*mlx_lib;
}				t_game;

#endif