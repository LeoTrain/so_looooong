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

void	set_player_pos(t_data *data, t_position pos)
{
	data->map.player_tile_position.x = pos.x;
	data->map.player_tile_position.y = pos.y;
	data->map.player_position.x = pos.x * TILE_SIZE + TILE_SIZE;
	data->map.player_position.y = (pos.y * TILE_SIZE) + TILE_SIZE;
}
