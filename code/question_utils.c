/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:40:38 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 17:05:59 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_next_tile_wall(t_data *data, int x, int y)
{
	get_player_pos(data);
	int next_x = data->player_position.x + x;
	int next_y = data->player_position.y + y;
	if (next_x < 0 || next_x >= data->map.size.x / TILE_SIZE || next_y < 0 || next_y >= data->map.size.y / TILE_SIZE)
		return (1);
	if (data->map.map[next_y][next_x] == '1')
		return (1);
	return (0);
}


int	is_on_exit(t_data *data)
{
	get_player_pos(data);
	return (data->player_position.x == data->exit_position.x && data->player_position.y == data->exit_position.y);
}
