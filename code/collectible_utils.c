/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:36:46 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 17:14:21 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "so_long.h"
#include <fcntl.h>

int count_coullectible(t_data *data)
{
	int		count;
	int		fd;
	char	*line;
	int		i;

	count = 0;
	fd = open(data->map.path, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == 'C')
				count++;
			i++;
		}
		free(line);
	}
	close(fd);
	return (count);
}

int	get_total_collected(t_data *data)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < data->collectibles.count)
	{
		if (data->collectibles.collectibles[i].collected)
			count++;
		i++;
	}
	return (count);
}

void add_collectible(t_data *data, t_position pos)
{
	t_collectible new_collectible;
	new_collectible.position = pos;
	new_collectible.collected = false;
	data->collectibles.collectibles[data->collectibles.count] = new_collectible;
	data->collectibles.count++;
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

void	sort_collectibles(t_data *data)
{
	t_collectible	current;
	t_collectible	next;
	t_collectible	temp;

	current = data->collectibles.collectibles[0];
	while (1)
	{
		int swapped = 0;
		for (int i = 0; i < data->collectibles.count - 1; i++)
		{
			current = data->collectibles.collectibles[i];
			next = data->collectibles.collectibles[i + 1];
			if (current.position.y > next.position.y ||
				(current.position.y == next.position.y && current.position.x > next.position.x))
			{
				temp = current;
				data->collectibles.collectibles[i] = next;
				data->collectibles.collectibles[i + 1] = temp;
				swapped = 1;
			}
		}
		if (!swapped)
			break;
	}
}

int is_all_collectibles_collected(t_data *data)
{
	for (int i = 0; i < data->map.size.y / TILE_SIZE; i++)
	{
		for (int j = 0; j < data->map.size.x / TILE_SIZE; j++)
		{
			if (data->map.map[i][j] == 'C')
				return (0);
		}
	}
	return (1);
}

int	is_on_collectible(t_data *data)
{
	int	i;

	get_player_pos(data);
	i = 0;
	// printf("HERE\n");
	// printf("Map at x:%d y:%d = %c\n", data->player_position.x, data->player_position.y, data->map.map[data->player_position.y][data->player_position.x]);
	if (data->map.map[data->player_position.y][data->player_position.x] == 'C')
	{
		while (i < data->collectibles.count)
		{
			if (data->collectibles.collectibles[i].position.x == data->player_position.x &&
				data->collectibles.collectibles[i].position.y == data->player_position.y)
			{
				data->map.map[data->player_position.y][data->player_position.x] = '0';
				data->collectibles.collectibles[i].collected = true;
				printf("You've collected a coin baby.\n");
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int	is_wall_at(t_data *data, int x, int y)
{
	printf("if (%d < 0 || %d >= %d || %d < 0 || %d >= %d\n)", x, x, data->map.size.x / TILE_SIZE, y, y, data->map.size.y / TILE_SIZE);
	p_position((t_position){data->map.size.x / TILE_SIZE, data->map.size.y / TILE_SIZE}, "Map size");
	printf("Map: %d\n", data->map.map[y][x]);
    if (x < 0 || x >= data->map.size.x / TILE_SIZE || y < 0 || y >= data->map.size.y / TILE_SIZE) 
        return (1);
    if (data->map.map[y][x] == '1')
        return (1);
    return (0);
}


// static t_position get_next_step(t_data *data, t_position target)
// {
//
// 	// p_position(data->player_position, "Player_position");
// 	// p_position(target, "Target");
// 	if (target.y < data->player_position.y && !is_next_tile_wall(data, 0, -1))
// 	{
// 		return ((t_position){0, -1});
// 	}
// 	else if (target.y > data->player_position.y && !is_next_tile_wall(data, 0, 1))
// 	{
// 		return ((t_position){0, 1});
// 	}
// 	else if (target.y == data->player_position.y)
// 	{
// 		if (target.x < data->player_position.x && !is_next_tile_wall(data, -1, 0))
// 			return ((t_position){-1, 0});
// 		else if (target.x > data->player_position.x && !is_next_tile_wall(data, 1, 0))
// 			return ((t_position){1, 0});
// 		return ((t_position){0, 0});
// 	}
// 	return ((t_position){0, 0});
// }

void	init_directions(t_position *directions)
{
	directions[0] = (t_position){-1, 0};
	directions[1] = (t_position){1, 0};
	directions[2] = (t_position){0, -1};
	directions[3] = (t_position){0, 1};
}

t_bool	is_valid(t_position position, int width, int height)
{
	return (position.x > 0 && position.x < width && position.y > 0 && position.y < height);
}

t_bool	is_same(t_position a, t_position b)
{
	return (a.x == b.x && a.y == b.y);
}


t_bool	get_path(t_position start, t_position end, char **map, t_bool **visited, int width, int height, t_position *path, int *path_length)
{
	t_position directions[4];
	t_position	next;
	init_directions(directions);
	if (!is_valid(start, width, height) || visited[start.y][start.x] || map[start.y][start.x] == '1')
		return (false);
	if (is_same(start, end))
	{
		path[*path_length] = start;
		(*path_length)++;
		return (true);
	}
	visited[start.y][start.x] = true;
	path[*path_length] = start;
	(*path_length)++;
	int i = 0;
	while (i < 4)
	{
		next = (t_position){start.x + directions[i].x, start.y + directions[i].y};
		if (get_path(next, end, map, visited, width, height, path, path_length))
			return (true);
		i++;
	}
	(*path_length)--;
	return (false);
}

void	move_player_path(t_data *data)
{
	t_position	next;
	int			x;
	int			y;

	if (!data->moving || data->path_index >= data->path_length)
	{
		data->moving = false;
		return ;
	}
	next = data->path[data->path_index];
	x = data->player_position.x - next.x;
	y = data->player_position.y - next.y;
	printf("Next x: %d | y: %d\n", x, y);

	if (x == 1)
		data->offset.x += TILE_SIZE;
	else if (x == -1)
		data->offset.x -= TILE_SIZE;
	else
		if (y <= 1 && y >= -1)
		{
			if (y == 1)
				data->offset.y += TILE_SIZE;
			else if (y == -1)
				data->offset.y -= TILE_SIZE;
		}
	get_player_pos(data);
	data->path_index++;
}

void move_to_collectible(t_data *data, t_collectible *collectible)
{
	int width = data->map.size.x / TILE_SIZE;
	int height = data->map.size.y / TILE_SIZE;
	t_bool	**visited = malloc(height * sizeof(t_bool *));
	int i = 0;

	while (i < height)
		visited[i++] = calloc(width, sizeof(t_bool));
	while (collectible->collected == true)
		collectible++;
	if (is_all_collectibles_collected(data))
	{
		printf("All collectibles are collected! Checking for exit.\n");
		get_path(data->player_position, data->map.exit_position, data->map.map, visited, width, height, data->path, &data->path_length);

	}
	else
		get_path(data->player_position, collectible->position, data->map.map, visited, width, height, data->path, &data->path_length);
	data->path_index = 1;
	data->moving = true;

}
