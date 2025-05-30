/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:41:48 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 17:07:14 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_player_pos(t_data *data)
{
	if (!data->player_position.x || !data->player_position.y)
		data->player_position = (t_position){-1, -1};
	int center_x = data->win_size / 2;
	int center_y = data->win_size / 2;
	data->player_position.x = ((center_x - data->offset.x) / TILE_SIZE) - 1;
	data->player_position.y = ((center_y - data->offset.y) / TILE_SIZE) - 1;
}
