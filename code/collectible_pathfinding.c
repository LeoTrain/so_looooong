/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_pathfinding.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:44:40 by leberton          #+#    #+#             */
/*   Updated: 2025/06/03 21:49:15 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


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

void	reset_visited(t_bool **visited, int width, int height)
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

void move_to_collectible(t_data *data, t_collectible *collectible)
{
	int width = data->map.size.x / TILE_SIZE;
	int height = data->map.size.y / TILE_SIZE;
	t_bool	**visited = malloc(height * sizeof(t_bool *));
	int i = 0;

	while (i < height)
		visited[i++] = calloc(width, sizeof(t_bool));
	if (is_all_collectibles_collected(data))
	{
		printf("All collectibles are collected! Checking for exit.\n");
		reset_visited(visited, width, height);
		get_path(data->player_position, data->exit_position, data->map.map, visited, width, height, data->path, &data->path_length);
	}
	else
		get_path(data->player_position, collectible->position, data->map.map, visited, width, height, data->path, &data->path_length);
	data->path_index = 1;
	data->moving = true;

}
