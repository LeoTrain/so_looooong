/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:41:48 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 14:41:53 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_player_pos(t_data *data)
{
	if (!data->player_pos)
		data->player_pos = malloc(sizeof(int) * 2);
	int center_x = data->win_size / 2;
	int center_y = data->win_size / 2;
	data->player_pos[0] = ((center_x - data->x_offset) / TILE_SIZE) - 1;
	data->player_pos[1] = ((center_y - data->y_offset) / TILE_SIZE) - 1;
}
