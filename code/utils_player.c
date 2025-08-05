/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:41:48 by leberton          #+#    #+#             */
/*   Updated: 2025/07/31 12:54:02 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_position	get_center_tile(t_data *data)
{
	t_position	center_offset;
	t_position	center_tile;

	if (!data->map.player_position.x || !data->map.player_position.y)
	{
		center_tile.x = -1;
		center_tile.y = -1;
		return (center_tile);
	}
	center_offset.x =(data->win_size / 2) - data->offset.x;
	center_offset.y =(data->win_size / 2) - data->offset.y;
	center_tile.x = (center_offset.x / TILE_SIZE) - 1;
	center_tile.y = (center_offset.y / TILE_SIZE) - 1;
	return (center_tile);
}

void	set_player_pos(t_data *data, t_position pos)
{
	data->is_player_set = 1;
	data->map.player_position.x = pos.x;
	data->map.player_position.y = pos.y;
}

void	get_player_pos(t_data *data)
{
	set_player_pos(data, get_center_tile(data));
}
