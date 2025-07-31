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
	data->player_position.x = pos.x;
	data->player_position.y = pos.y;
}

void	get_player_pos(t_data *data)
{
	t_position	center;
	t_position	start;

	if (!data->player_position.x || !data->player_position.y)
	{
		start.x = -1;
		start.y = -1;
		set_player_pos(data, start);
		return ;
	}
	center.x = (((data->win_size / 2) - data->offset.x) / TILE_SIZE) - 1;
	center.y = (((data->win_size / 2) - data->offset.y) / TILE_SIZE) - 1;
	set_player_pos(data, center);
}
