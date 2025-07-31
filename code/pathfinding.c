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

static void	reset_visited(t_data *data)
{
	t_position	size;
	t_position	pos;

	size.x = data->map.size.y / TILE_SIZE;
	size.y = data->map.size.x / TILE_SIZE;
	while (size.y - 1 > 0)
	{
		while (size.x - 1 >= 0)
		{
			pos.x = size.x - 1;
			pos.y = size.y - 1;
			if (is_valid_position(pos, data))
				data->map.visited[pos.y][pos.x] = false;
			size.x--;
		}
		size.y--;
	}
}

static t_bool	get_path(t_position start, t_position end, t_data *data)
{
	t_position	directions[4];
	int			i;

	init_directions(directions);
	if (!is_valid_position(start, data))
		return (false);
	if (is_same(start, end))
	{
		data->path[data->path_length] = start;
		data->path_length++;
		return (true);
	}
	data->map.visited[start.y][start.x] = true;
	data->path[data->path_length] = start;
	data->path_length++;
	i = 0;
	while (i < 4)
	{
		if (get_path(add_positions(start, directions[i]), end, data))
			return (true);
		i++;
	}
	data->path_length--;
	return (false);
}

static void	take_action(t_data *data, t_collectible *collectible)
{
	if (is_all_collectibles_collected(data))
	{
		reset_visited(data);
		get_path(data->map.player_position, data->map.exit_position, data);
	}
	else
		get_path(data->map.player_position, collectible->position, data);
	data->path_index = 1;
	data->moving = true;
}

void move_to_collectible(t_data *data, t_collectible *collectible)
{
	take_action(data, collectible);
}
