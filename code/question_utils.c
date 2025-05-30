/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:40:38 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 14:42:34 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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


int	is_on_exit(t_data *data)
{
	get_player_pos(data);
	if (data->exit_pos && data->player_pos[0] == data->exit_pos[1] && data->player_pos[1] == data->exit_pos[0])
		return (1);
	return (0);
}
