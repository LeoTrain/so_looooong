/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_pathfinding_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:49:44 by leberton          #+#    #+#             */
/*   Updated: 2025/06/03 21:51:15 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_directions(t_position *directions)
{
	directions[0] = (t_position){-1, 0};
	directions[1] = (t_position){1, 0};
	directions[2] = (t_position){0, -1};
	directions[3] = (t_position){0, 1};
}

t_bool	is_same(t_position a, t_position b)
{
	return (a.x == b.x && a.y == b.y);
}

static t_bool	is_valid(t_position position, int width, int height)
{
	return (position.x > 0 && position.x < width && position.y > 0 && position.y < height);
}

void	free_visited(t_bool **visited, t_data *data)
{
	int		i;

	i = 0;
	while (i < data->map.size.y / TILE_SIZE)
		free(visited[i++]);
	free(visited);
}

t_bool	is_valid_position(t_position pos, t_bool **visited, t_data *data)
{
	if (!is_valid(pos, data->map.size.x / TILE_SIZE, data->map.size.y / TILE_SIZE))
			return (false);
	if (visited[pos.y][pos.x] || data->map.map[pos.y][pos.x] == '1')
		return (false);
	return (true);
}
