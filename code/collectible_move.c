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

void	move_player_path(t_data *data)
{
	t_position	next;
	int			x;
	int			y;

	if (!data->moving || data->path_index >= data->path_length)
	{
		data->moving = false;
		return ;
	}
	next = data->path[data->path_index];
	x = data->player_position.x - next.x;
	y = data->player_position.y - next.y;
	if (x == 1)
		data->offset.x += TILE_SIZE;
	else if (x == -1)
		data->offset.x -= TILE_SIZE;
	else
		if (y <= 1 && y >= -1)
		{
			if (y == 1)
				data->offset.y += TILE_SIZE;
			else if (y == -1)
				data->offset.y -= TILE_SIZE;
		}
	if (is_on_collectible(data))
		printf("You are on a collectible.\n");
	else if (is_on_exit(data))
	{
		printf("You are on the exit.\n");
		free_all(data);
		exit(0);
	}
	data->path_index++;
}
