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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		win_size;
	int		x;
	int		y;
	int		x_offset;
	int		y_offset;
	char	*character_xpm_path;
	void	*character_img;
	char	*grass_xpm_path;
	void	*grass_img;
	char	*wall_xpm_path;
	void	*wall_img;
	char	*collectible_xpm_path;
	void	*collectible_img;
	char	*mapexit_xpm_path;
	void	*mapexit_img;
	char	*map_path;
	int		map_width;
	char	map_x;
	int		map_height;
	int		left_limit;
	int		right_limit;
	int		last_move_dir;
	char	**map;
	int		*player_pos;
	int		*exit_pos;
	t_list	*collectibles;
	int		collected_collectibles;
	int		collectibles_total;
	int		tile_size;
}			t_data;


char	*ft_strdup(const char *s);
void	ft_lstadd_back(t_list **lst, t_list *n);
void	ft_lstadd_front(t_list **lst, t_list *n);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void	*content);
int     ft_lstsize(t_list *lst);
long	get_time_in_ms(void);
int	get_map_measurements(t_data *data);
void	remove_collectible(t_data *data, t_list *target, t_list *previous);
void	sort_collectibles(t_data *data);
void	load_image(void *mlx, void **img, char *path, int *w, int *h);
int is_all_collectibles_collected(t_data *data);
int	is_on_collectible(t_data *data);
void	move_to_collectible(t_data *data, t_list *collectible);
void	get_player_pos(t_data *data);
int	is_next_tile_wall(t_data *data, int x, int y);
int	is_on_exit(t_data *data);
int ft_pcoll(t_list *data);
int	key_hook(int keycode, t_data *data);
int	loop_hook(t_data *data);

#endif
