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
}			t_data;


void	p_position(t_position position, char *name);
int count_coullectible(t_data *data);
t_queue	*queue_new(void);
void		queue_push(t_queue *q, t_position pos);
t_position	queue_pop(t_queue *q);
int			queue_empty(t_queue *q);
void		queue_free(t_queue *q);
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
void	move_to_collectible(t_data *data, t_collectible *collectible);
void	get_player_pos(t_data *data);
int	is_next_tile_wall(t_data *data, int x, int y);
int	is_on_exit(t_data *data);
int ft_pcoll(t_list *data);
int	key_hook(int keycode, t_data *data);
int	loop_hook(t_data *data);
void add_collectible(t_data *data, t_position pos);


#endif
