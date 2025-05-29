/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:33:03 by leberton          #+#    #+#             */
/*   Updated: 2025/05/26 16:59:31 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <stdio.h>

#define TILE_SIZE 16

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

void	load_image(void *mlx, void **img, char *path, int *w, int *h)
{
	*img = mlx_xpm_file_to_image(mlx, path, w, h);
}


int	get_map_measurements(t_data *data)
{
	int		fd;
	char	*line;
	char	*e;
	int		i = 0;

	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	data->map_height = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		data->map_height++;
		free(line);
	}
	close(fd);
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (0);
	fd = open(data->map_path, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		data->map[i] = ft_strdup(line);
		if ((e = strchr(line, 'P')))
		{
			int player_pos_y = i * TILE_SIZE + 16;
			int player_pos_x = ((int)(e - line) * TILE_SIZE) + 16;
			data->x_offset = (data->win_size / 2) - player_pos_x;
			data->y_offset = (data->win_size / 2) - player_pos_y;
		}
		if ((e = strchr(line, 'E')) && !data->exit_pos)
		{
			data->exit_pos = (int *)calloc(2, sizeof(int));
			data->exit_pos[0] = i;
			data->exit_pos[1] = (int)(e - line);
		}
		if ((e = strchr(line, 'C')))
		{
			char *pos = line;
			while ((pos = strchr(pos, 'C')) != NULL)
			{
				printf("Collectible found at (%d, %ld)\n", i, pos - line);
				t_list *new_collectible = ft_lstnew(NULL);
				new_collectible->content = malloc(sizeof(int) * 2);
				((int *)new_collectible->content)[0] = i;
				((int *)new_collectible->content)[1] = (int)(pos - line);
				ft_lstadd_front(&data->collectibles, new_collectible);
				pos++;
				data->collectibles_total++;
			}
		}
		i++;
		data->map_width = strlen(line) * TILE_SIZE;
		free(line);
	}
	data->map[i] = NULL;
	data->map_height *= TILE_SIZE;
	close(fd);
	return (1);
}



void	get_player_pos(t_data *data)
{
	if (!data->player_pos)
		data->player_pos = malloc(sizeof(int) * 2);
	int center_x = data->win_size / 2;
	int center_y = data->win_size / 2;
	data->player_pos[0] = ((center_x - data->x_offset) / TILE_SIZE) - 1;
	data->player_pos[1] = ((center_y - data->y_offset) / TILE_SIZE) - 1;
}

long	get_time_in_ms(void)
{
	struct	timeval	timev;
	gettimeofday(&timev, NULL);
	return (timev.tv_sec * 1000 + timev.tv_usec / 1000);
}

void	remove_collectible(t_data *data, t_list *target, t_list *previous)
{
	if (previous)
	   previous->next = target->next;
	else
	   data->collectibles = target->next;
	free(target->content);
	free(target);
}

void	sort_collectibles(t_data *data)
{
	t_list	*current;
	t_list	*next;
	int		temp[2];

	current = data->collectibles;
	while (current && current->next)
	{
		next = current->next;
		while (next)
		{
			if (((int *)current->content)[0] > ((int *)next->content)[0] ||
				(((int *)current->content)[0] == ((int *)next->content)[0] &&
				((int *)current->content)[1] > ((int *)next->content)[1]))
			{
				temp[0] = ((int *)current->content)[0];
				temp[1] = ((int *)current->content)[1];
				((int *)current->content)[0] = ((int *)next->content)[0];
				((int *)current->content)[1] = ((int *)next->content)[1];
				((int *)next->content)[0] = temp[0];
				((int *)next->content)[1] = temp[1];
			}
			next = next->next;
		}
		current = current->next;
	}
}

int	is_next_tile_wall(t_data *data, int x, int y)
{
	get_player_pos(data);
	int next_x = data->player_pos[0] + x;
	int next_y = data->player_pos[1] + y;
	if (next_x < 0 || next_x >= data->map_width / TILE_SIZE ||
		next_y < 0 || next_y >= data->map_height / TILE_SIZE)
	{
		return (1);
	}
	if (data->map[next_y][next_x] == '1')
	{
		return (1);
	}
	return (0);
}

int is_all_collectibles_collected(t_data *data)
{
	return (data->collected_collectibles == data->collectibles_total);
}

int	is_on_exit(t_data *data)
{
	get_player_pos(data);
	if (data->exit_pos && data->player_pos[0] == data->exit_pos[1] && data->player_pos[1] == data->exit_pos[0])
		return (1);
	return (0);
}

int	is_on_collectible(t_data *data)
{
	t_list	*previous;
	t_list	*current;

	previous = NULL;
	current = data->collectibles;

	while (current)
	{
		int *pos = (int *)current->content;
		if (pos[0] == data->player_pos[1] && pos[1] == data->player_pos[0])
		{
			data->map[pos[0]][pos[1]] = '0';
			data->collected_collectibles++;
			remove_collectible(data, current, previous);
			return (1);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}

void	free_all(t_data *data)
{
	if (data->character_img)
		mlx_destroy_image(data->mlx, data->character_img);
	if (data->grass_img)
		mlx_destroy_image(data->mlx, data->grass_img);
	if (data->wall_img)
		mlx_destroy_image(data->mlx, data->wall_img);
	if (data->collectible_img)
		mlx_destroy_image(data->mlx, data->collectible_img);
	if (data->mapexit_img)
		mlx_destroy_image(data->mlx, data->mapexit_img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->player_pos)
		free(data->player_pos);
	if (data->exit_pos)
		free(data->exit_pos);
	if (data->map)
	{
		for (int i = 0; data->map[i]; i++)
			free(data->map[i]);
		free(data->map);
	}
}

void	move_to_collectible(t_data *data, t_list *collectible)
{
	int *pos = (int *)collectible->content;
	int *player_pos = data->player_pos;

	printf("Moving to collectible at (%d, %d)\n", pos[0], pos[1]);
	printf("Player position is (%d, %d)\n", player_pos[0], player_pos[1]);

	if (pos[1] < player_pos[1] && !is_next_tile_wall(data, -1, 0))
		data->x_offset += TILE_SIZE;
	else if (pos[1] > player_pos[1] && !is_next_tile_wall(data, 1, 0))
		data->x_offset -= TILE_SIZE;
	else if (pos[0] < player_pos[0] && !is_next_tile_wall(data, 0, -1))
		data->y_offset += TILE_SIZE;
	else if (pos[0] > player_pos[0] && !is_next_tile_wall(data, 0, 1))
		data->y_offset -= TILE_SIZE;
	else
	{
		printf("Cannot move to collectible at (%d, %d) due to walls.\n", pos[0], pos[1]);
		printf("Collectibles size: %d\n", ft_lstsize(data->collectibles));

	}

	if (is_on_collectible(data))
		printf("You collected %d collectibles!\n", data->collected_collectibles);
}


int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 119 && !is_next_tile_wall(data, 0, -1))
		data->y_offset += TILE_SIZE;
	else if (keycode == 115 && !is_next_tile_wall(data, 0, 1))
		data->y_offset -= TILE_SIZE;
	else if (keycode == 97 && !is_next_tile_wall(data, -1, 0))
		data->x_offset += TILE_SIZE;
	else if (keycode == 100 && !is_next_tile_wall(data, 1, 0))
		data->x_offset -= TILE_SIZE;
	if (is_on_exit(data))
	{
		if (!is_all_collectibles_collected(data))
		{
			printf("You need to collect all collectibles before exiting!\n");
			return (0);
		}
		printf("You reached the exit!\n");
		exit(0);
	}
	if (is_on_collectible(data))
	{
		printf("You collected %d collectibles!\n", data->collected_collectibles);
	}
	return (0);
}

void	draw(t_data *data)
{

	mlx_clear_window(data->mlx, data->win);
	int i = 0;
	int row = 0;
	while (data->map[row])
	{
		for (i = 0; i < data->map_width; i++)
		{
			int pos_x = (TILE_SIZE * i) + data->x_offset;
			int pos_y = (row * TILE_SIZE) + data->y_offset;
			if (data->map[row][i] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->wall_img, pos_x, pos_y);
			else if (data->map[row][i] == '0')
				mlx_put_image_to_window(data->mlx, data->win, data->grass_img, pos_x, pos_y);
			else if (data->map[row][i] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->collectible_img, pos_x, pos_y);
		}
		row++;
	}
	int player_pos_y = (data->win_size / 2) - 16;
	int player_pos_x = (data->win_size / 2) - 16;
	mlx_put_image_to_window(data->mlx, data->win, data->character_img, player_pos_x, player_pos_y);
	// mlx_put_image_to_window(data->mlx, data->win, data->character_img, (data->win_size / 2)-(data->character_width/2), (data->win_size/2)-(data->character_height/2));
}

int	loop_hook(t_data *data)
{
	static long	last_time;
	long		current_time;

	if (last_time == 0)
		last_time = get_time_in_ms();
	current_time = get_time_in_ms();

	if (current_time - last_time >= 100)
	{
		last_time = current_time;
		draw(data);
		move_to_collectible(data, data->collectibles);
	}
	return (0);
}

int	ft_puterror(char *message, int error_code)
{
	printf("%s\n", message);
	return (error_code);
}

int ft_pcoll(t_list *data)
{
	t_list *curr = data;
	int i = 1;
	while (curr)
	{
		printf("Collectible %d: (%d, %d)\n", i,
			((int *)curr->content)[0],
			((int *)curr->content)[1]);
		curr = curr->next;
		i++;
	}
	printf("\n\n\n");
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_puterror("Error: correct use case ./program_name <map.file>.", 1));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_puterror("Error: creating the mlx variable.", 2));
	data.win_size = 20 * TILE_SIZE;
	data.win = mlx_new_window(data.mlx, data.win_size, data.win_size, "Test1");
	if (!data.win)
		return (ft_puterror("Error: creating the window.", 2));
	data.character_xpm_path = "assets/xpm/normal_amazed.xpm";
	data.grass_xpm_path = "assets/empty_space.xpm";
	data.wall_xpm_path = "assets/wall.xpm";
	data.collectible_xpm_path = "assets/collectible.xpm";
	data.mapexit_xpm_path = "assets/exit.xpm";
	load_image(data.mlx, (void **)&data.character_img, data.character_xpm_path, &data.tile_size, &data.tile_size);
	load_image(data.mlx, (void **)&data.grass_img, data.grass_xpm_path, &data.tile_size, &data.tile_size);
	load_image(data.mlx, (void **)&data.wall_img, data.wall_xpm_path, &data.tile_size, &data.tile_size);
	load_image(data.mlx, (void **)&data.collectible_img, data.collectible_xpm_path, &data.tile_size, &data.tile_size);
	data.map = NULL;
	data.map_path = argv[1];
	data.x = 0;
	data.y = 0;
	data.exit_pos = NULL;
	data.collectibles = NULL;
	data.collected_collectibles = 0;
	data.collectibles_total = 0;
	if (!get_map_measurements(&data))
		return (ft_puterror("Error: reading the map file.", 3));
	get_player_pos(&data);
	ft_pcoll(data.collectibles);
	sort_collectibles(&data);
	ft_pcoll(data.collectibles);
	
	mlx_key_hook(data.win, (int (*)(int, void *))key_hook, &data);
	mlx_loop_hook(data.mlx, (int (*)(void *))loop_hook, &data);
	mlx_loop(data.mlx);

	free_all(&data);

	return (0);
}
