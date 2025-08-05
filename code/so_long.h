#ifndef SO_LONG_H
#define SO_LONG_H

#include "minilibx-linux/mlx.h"
#include "get_next_line.h"
#include "ft_printf/headers/ft_printf.h"
#include "ft_printf/headers/libft.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>

#define TILE_SIZE 64

typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef enum e_simple_direction
{
	left = -1,
	right = 1,
	down = -1,
	up = 1,
	stand = 0
}	t_simple_direction;

typedef struct s_position
{
	int		x;
	int		y;
}		t_position;

typedef struct s_xpm_img
{
	char	*path;
	void	*img;
}			t_xpm_img;

typedef struct s_assets
{
	t_xpm_img	character;
	t_xpm_img	grass;
	t_xpm_img	wall;
	t_xpm_img	collectible;
	t_xpm_img	exit;
}				t_assets;

typedef struct s_map
{
	char		**map;
	char		**map_is_makeable;
	char		*path;
	t_position	size;
	t_position	tile_size;
	t_bool		**visited;
	t_position	exit_position;
	t_position	player_position;
}				t_map; // Add collectibles to the map

typedef struct s_collectible
{
	t_position	position;
	t_bool		collected;
}				t_collectible;

typedef struct s_collectible_list
{
	t_collectible	*collectibles;
	int				count; }					t_collectible_list;
typedef struct s_data
{
	void				*mlx;
	void				*win;
	int					win_size;
	int					x;
	int					y;
	t_position			offset;
	t_assets			assets;
	t_map				map;
	t_collectible_list	collectibles;
	t_position			path[1000];
	int					path_length;
	int					path_index;
	t_bool				moving;
	int					found_collectible;
	int					found_exit;
	int					current_moves;
	int					is_player_set;
}						t_data;

int		exit_error(char *message, t_data *data);
int		exit_success(char *message, t_data *data);
int		ft_strcmp(char *s1, char *s2);

t_bool	is_x_bigger(struct s_position a, struct s_position b);
t_position add_positions(t_position a, t_position b);
void	init_game(t_data *data, char *map_path);
void	init_directions(t_position *directions); // Change to t_bool
t_bool	load_image(void *mlx, void **img, char *path, int *w, int *h);

t_bool	is_valid_position(t_position pos, t_data *data);
t_bool	is_same(t_position a, t_position b);
int		is_all_collectibles_collected(t_data *data); // Change to t_bool
int		is_on_collectible(t_data *data); // Change to t_bool
t_bool	is_next_tile_wall(t_data *data, int x, int y);
t_bool	is_on_exit(t_data *data);

int		count_coullectible(t_data *data);
void	sort_collectibles(t_data *data);
void	move_to_collectible(t_data *data, t_collectible *collectible);
void	add_collectible(t_data *data, t_position pos);
void	set_map(t_data	*data);
int		get_map_measurements(t_data *data);
void	get_player_pos(t_data *data);
void	set_player_pos(t_data *data, t_position pos);
void	move_player_path(t_data *data);

long	get_time_in_ms(void);
void	draw(t_data *data);
int		key_hook(int keycode, t_data *data);
int		loop_hook(t_data *data);
void	free_all(t_data *data);

void	move(char *direction, t_data *data);

void	load_all_images(t_data *data);
void	create_collectibles(t_data *data);
void	free_current_visited(t_data *data, int i);
void	allocate_visited_array_row(t_data *data, t_position map_tile_size);
void	create_visited(t_data *data);

void	check_is_makeable(t_data *data, int x, int y);
void	is_makeable(t_data *data);
void	free_map(t_data *data, int and_map);

#endif
