#ifndef STRUCT_H
# define STRUCT_H
typedef struct s_player
{
	float			x;
	float			y;
	float			z;
}					t_player;








typedef struct s_map
{
	char **map;       // the hole map
	char map_char[6]; // allowed chars
						// u must also add the player loc
}					t_map;



typedef enum e_type_of_text
{
	NO,
	SO,
	WE,
	EA
}					t_type_of_text;
typedef struct s_texture
{
	t_type_of_text	type;
	char			*path;
}					t_texture;

typedef struct s_config
{
	int				fd;
	int count_of_elements;
	t_texture *texture; // texture path checks NO,SO,WE,EA
	char			*floor;
	char 			*ceiling; // floor and ceiling F or C with (220,100,0)
	char *save_line_map;
	t_map			*map;
}					t_config;

typedef struct s_game
{
	t_config		*config_file_data;
	t_player		*player;
}					t_game;

#endif