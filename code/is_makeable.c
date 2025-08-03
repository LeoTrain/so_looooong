/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_makeable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:06:50 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 20:41:36 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_map_at_pos(t_data *data, int x, int y)
{
	if (data->map.map[y][x] == '1' || data->map.map[y][x] == 'V')
		return (-1);
	if (data->map.map[y][x] == 'C')
		data->found_collectible++;
	if (data->map.map[y][x] == 'E')
		data->found_exit = 1;
	data->map.map[y][x] = 'V';
	return (1);
}

void	check_is_makeable(t_data *data, int x, int y)
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
	check_is_makeable(data, data->map.player_position.x, data->map.player_position.y);
	if (data->found_collectible != data->collectibles.count || data->found_exit != 1)
		ft_puterror("Error\neither not found all collectibles or no exit.", data);
}
