/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:06:50 by leberton          #+#    #+#             */
/*   Updated: 2025/08/07 11:35:55 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_map_at_pos(t_data *data, int x, int y)
{
	if (data->map.map_is_makeable[y][x] == '1'
		|| data->map.map_is_makeable[y][x] == 'V')
		return (-1);
	if (data->map.map_is_makeable[y][x] == 'C')
		data->found_collectible++;
	if (data->map.map_is_makeable[y][x] == 'E')
		data->found_exit = 1;
	data->map.map_is_makeable[y][x] = 'V';
	return (1);
}

static void	check_is_makeable(t_data *data, int x, int y)
{
	if (check_map_at_pos(data, x, y) == -1)
		return ;
	check_is_makeable(data, x + 1, y);
	check_is_makeable(data, x - 1, y);
	check_is_makeable(data, x, y + 1);
	check_is_makeable(data, x, y - 1);
}

void	is_makeable(t_data *data)
{
	int	x;
	int	y;

	data->found_collectible = 0;
	x = data->map.player_tile_position.x;
	y = data->map.player_tile_position.y;
	check_is_makeable(data, x, y);
	if (data->found_collectible != data->collectibles.count)
		exit_error("Error\nnot found all collectibles.\n", data);
	if (data->found_exit != 1)
		exit_error("Error\nnot found the exit.\n", data);
}
