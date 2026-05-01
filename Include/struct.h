#ifndef STRUCT_H
# define STRUCT_H
typedef struct s_player
{
	int			x;
	int			y;
}				t_player;
typedef struct s_config
{
}				t_config;

typedef struct s_game
{
	t_config	**map;
	t_player	*player;
}				t_game;

#endif