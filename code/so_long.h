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
	t_position	exit_position;
	t_position	player_position;
	t_position	player_tile_position;
}				t_map;

typedef struct s_collectible
{
	t_position	position;
	int			collected;
}				t_collectible;

typedef struct s_collectible_list
{
	t_collectible	*collectibles;
	int				count;
}					t_collectible_list;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	int					win_width;
	int					win_height;
	t_position			offset;
	t_assets			assets;
	t_map				map;
	t_collectible_list	collectibles;
	int					found_collectible;
	int					found_exit;
	int					current_moves;
	int					is_player_set;
	int					is_exit_set;
	int					current_fd;
}						t_data;

int		exit_error(char *message, t_data *data);
int		exit_success(char *message, t_data *data);
int		pressed_on_x(void *data);
int		ft_strcmp(char *s1, char *s2);

void	init_game(t_data *data, char *map_path);
int		load_image(void *mlx, void **img, char *path, int *w, int *h);
void	load_all_images(t_data *data);

int		is_same(t_position a, t_position b);
int		is_all_collectibles_collected(t_data *data); // Change to t_bool
int		is_on_collectible(t_data *data); // Change to t_bool
int		is_next_tile_wall(t_data *data, int x, int y);
int		is_on_exit(t_data *data);

void	create_collectibles(t_data *data);
void	add_collectible(t_data *data, t_position pos);
void	get_map_size(t_data *data);
void	set_map(t_data	*data);
void	set_collectible(t_data *data, int y, char *line);
void	set_exit(t_data *data, int y, char *line, char *e);
void	set_player(t_data *data, int y, char *line, char *e);
void	parse_map(t_data *data);
void	allocate_for_map(t_data	*data);
void	get_map_measurements(t_data *data);
void	set_player_pos(t_data *data, t_position pos);

long	get_time_in_ms(void);
void	draw(t_data *data);
int		key_hook(int keycode, t_data *data);
int		loop_hook(t_data *data);
void	free_all(t_data *data);

void	move(char *direction, t_data *data);

void	is_makeable(t_data *data);

#endif
