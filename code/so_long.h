#ifndef SO_LONG_H
#define SO_LONG_H

#include "minilibx-linux/mlx.h"
#include "get_next_line/get_next_line.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>

#define TILE_SIZE 16

typedef struct s_queue t_queue;

typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_position
{
	int x;
	int y;
}	t_position;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_xpm_img
{
	char    *path;
	void	*img;
}	t_xpm_img;

typedef struct s_assets
{
	t_xpm_img character;
	t_xpm_img grass;
	t_xpm_img wall;
	t_xpm_img collectible;
	t_xpm_img exit;
}	t_assets;

typedef struct s_map
{
	char	  **map;
	char	  *path;
	t_position size;
	t_position tile_size;
	t_position exit_position;
	t_position player_position;
}	t_map;

typedef struct s_collectible
{
	t_position position;
	t_bool       collected;
}	t_collectible;

typedef struct s_collectible_list
{
	t_collectible *collectibles;
	int           count;
}	t_collectible_list;

typedef struct s_data
{
	void	           *mlx;
	void	           *win;
	int		           win_size;
	int		           x;
	int		           y;
	t_position	       offset;
	t_position	       exit_position;
	t_position	       player_position;
	t_assets	       assets;
	t_map	           map;
	t_collectible_list collectibles;
	int		           *player_pos;
	int		           *exit_pos;
	t_position			path[100];
	int					path_length;
	int					path_index;
	t_bool				moving;
}			t_data;

int		ft_puterror(char *message, int error_code);
char	*ft_strdup(const char *s);
int		count_coullectible(t_data *data);
int		get_map_measurements(t_data *data);
t_bool	init_game(t_data *data, char *map_path);
long	get_time_in_ms(void);
void	sort_collectibles(t_data *data);
t_bool	load_image(void *mlx, void **img, char *path, int *w, int *h);
int is_all_collectibles_collected(t_data *data);
int	is_on_collectible(t_data *data);

void	init_directions(t_position *directions);
t_bool	is_valid(t_position position, int width, int height);
t_bool	is_same(t_position a, t_position b);
t_bool	get_path(t_position start, t_position end, char **map, t_bool **visited, int width, int height, t_position *path, int *path_length);
void	reset_visited(t_bool **visited, int width, int height);
void	move_to_collectible(t_data *data, t_collectible *collectible);
void	move_player_path(t_data *data);
void	get_player_pos(t_data *data);

void	draw(t_data *data);
int	is_next_tile_wall(t_data *data, int x, int y);
int	is_on_exit(t_data *data);
int	key_hook(int keycode, t_data *data);
int	loop_hook(t_data *data);
void add_collectible(t_data *data, t_position pos);


#endif
