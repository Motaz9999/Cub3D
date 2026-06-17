#ifndef STRUCT_H
# define STRUCT_H

// for queue and player
typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

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

// this i can take from it what i need later to use
typedef struct s_config
{
	int			fd;
	int			count_of_elements;
	char		*texture[6];
	// texture path checks NO,SO,WE,EA,C,F(see the enum to know what each index mean)
	char		*save_line_map;
	t_map		*map_data;
}				t_config;

typedef struct s_mlx
{
	void *mlx; // connection to display
	void *win; // the window here we want to put the img
	void *img; // the image buffer the img i want to print on the window
	char		*addr;
	// raw pixel array (pointer to the first pixel in the screen)  useed when we want to color pixel at x,y  on the img
	int			bpp;
	// bits per pixel  always its 32 its mean each pixel have 4bytes argb coloring  and to till what each time i move and how in the the adder
	int line_len; // bytes per row  used to get to the next row on the img
	int endian;   // byte order  we dont use it
}				t_mlx;

// have texture ready to use
typedef struct s_texture
{
	void		*no_texture;
	void		*so_texture;
	void		*we_texture;
	void		*ea_texture;
	int			c_color;
	int			f_color;
}				t_texture;

// this struct to keep moving smooth as possible
// like what if u press move and right together
// if i was on the simple way (handle key by key in key press it wont be smooth)
// and when i press w it must keep going until i  not pressing it
// so i must have 2 fun 1 for press and one for  not pressing
// event 2 -> press , event 3-> not pressing
typedef struct s_key
{
	int			w;
	int			d;
	int			s;
	int			a;
	int			right_arrow;
	int			left_arrow;
}				t_key;

// use when i make the raycasting
typedef struct s_player
{
	double		x;
	double		plane_len;
	double y; // moving is difference
	double		dir_x;
	double dir_y;   // where the player looking
	double plane_x; // the width for the whole FOV
	double		plane_y;
}				t_player;

typedef enum e_dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}				t_dir;

typedef struct s_game
{
	t_config	*config_file_data;
	t_mlx		*mlx_lib;
	t_texture	*loaded_texture;
	t_key		*keys;
	t_player	*player;
}				t_game;

typedef struct s_ray
{
	int			side;
	int			step_x;
	int			step_y;
	int			hit;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dest_x;
	double		side_dest_y;
}				t_ray;

#endif