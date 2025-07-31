/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pathfinding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:49:44 by leberton          #+#    #+#             */
/*   Updated: 2025/07/31 12:53:54 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_directions(t_position *directions)
{
	directions[0].x = left;
	directions[0].y = stand;
	directions[1].x = right;
	directions[1].y = stand;
	directions[2].x = stand;
	directions[2].y = down;
	directions[3].x = stand;
	directions[3].y = up;
}

t_bool	is_same(t_position a, t_position b)
{
	return (a.x == b.x && a.y == b.y);
}

static t_bool	is_valid(t_position position, t_data *data)
{
	t_position	map_tile_size;

	map_tile_size.x = data->map.size.x / TILE_SIZE;
	map_tile_size.y = data->map.size.y / TILE_SIZE;
	return (position.x > 0 && position.x < map_tile_size.x && position.y > 0 && position.y < map_tile_size.y);
}

void	free_visited(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->map.size.y / TILE_SIZE)
		free(data->map.visited[i++]);
	free(data->map.visited);
}

t_bool	is_valid_position(t_position pos, t_data *data)
{
	if (!is_valid(pos, data))
			return (false);
	if (data->map.visited[pos.y][pos.x] || data->map.map[pos.y][pos.x] == '1')
		return (false);
	return (true);
}
