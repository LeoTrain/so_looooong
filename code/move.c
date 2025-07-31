/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:51:43 by leberton          #+#    #+#             */
/*   Updated: 2025/06/03 21:51:53 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move(char *direction, t_data *data)
{
	if (strcmp(direction, "left") == 0)
		data->offset.x += TILE_SIZE;
	if (strcmp(direction, "right") == 0)
		data->offset.x -= TILE_SIZE;
	if (strcmp(direction, "down") == 0)
		data->offset.y += TILE_SIZE;
	if (strcmp(direction, "up") == 0)
		data->offset.y -= TILE_SIZE;
}

static void	set_offset(t_data *data, int x, int y)
{
	if (x == right)
		move("left", data);
	else if (x == left)
		move("right", data);
	else
	{
		if (y == up)
			move("down", data);
		else if (y == down)
			move("up", data);
	}
}

void	move_player_path(t_data *data)
{
	t_position	next;

	if (!data->moving || data->path_index >= data->path_length)
	{
		data->moving = false;
		return ;
	}
	next = data->path[data->path_index];
	next.x = data->map.player_position.x - next.x;
	next.y = data->map.player_position.y - next.y;
	set_offset(data, next.x, next.y);
	data->path_index++;
}
