/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_pathfinding.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:44:40 by leberton          #+#    #+#             */
/*   Updated: 2025/07/08 20:31:15 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_bool	get_path(t_position start, t_position end,
						t_bool **visited, t_data *data)
{
	t_position	directions[4];
	t_position	next;
	int			i;

	init_directions(directions);
	if (!is_valid(start, data->map.size.x / TILE_SIZE,
			data->map.size.y / TILE_SIZE) || visited[start.y][start.x]
			|| data->map.map[start.y][start.x] == '1')
		return (false);
	if (is_same(start, end))
	{
		data->path[data->path_length] = start;
		data->path_length++;
		return (true);
	}
	visited[start.y][start.x] = true;
	data->path[data->path_length] = start;
	data->path_length++;
	i = 0;
	while (i < 4)
	{
		next.x = start.x + directions[i].x;
		next.y = start.y + directions[i].y;
		if (get_path(next, end, visited, data))
			return (true);
		i++;
	}
	data->path_length--;
	return (false);
}

static void	reset_visited(t_bool **visited, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			visited[i][j] = false;
			j++;
		}
		i++;
	}
}

static void	take_action(t_data *data, t_bool **visited, t_collectible *collectible)
{
	if (is_all_collectibles_collected(data))
	{
		printf("All collectibles are collected! Checking for exit.\n");
		reset_visited(visited, data->map.size.x / TILE_SIZE, data->map.size.y / TILE_SIZE);
		get_path(data->player_position, data->exit_position, visited, data);
	}
	else
		get_path(data->player_position, collectible->position, visited, data);
	data->path_index = 1;
	data->moving = true;
}

void move_to_collectible(t_data *data, t_collectible *collectible)
{
	t_bool	**visited;

	visited = malloc((data->map.size.y / TILE_SIZE) * sizeof(t_bool *));
	if (!visited)
		return ;
	int i = 0;
	while (i < data->map.size.y / TILE_SIZE)
	{
		visited[i] = calloc(data->map.size.x / TILE_SIZE, sizeof(t_bool));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return ;
		}
		i++;
	}
	take_action(data, visited, collectible);
	i = 0;
	while (i < data->map.size.y / TILE_SIZE)
		free(visited[i++]);
	free(visited);
}
