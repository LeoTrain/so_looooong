/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:51:43 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 19:35:07 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move(char *direction, t_data *data)
{
	if (ft_strcmp(direction, "left") == 0)
	{
		data->offset.x += TILE_SIZE;
		data->map.player_tile_position.x--;
		data->map.player_position.x -= TILE_SIZE;
	}
	if (ft_strcmp(direction, "right") == 0)
	{
		data->offset.x -= TILE_SIZE;
		data->map.player_tile_position.x++;
		data->map.player_position.x += TILE_SIZE;
	}
	if (ft_strcmp(direction, "down") == 0)
	{
		data->offset.y += TILE_SIZE;
		data->map.player_tile_position.y--;
		data->map.player_position.y -= TILE_SIZE;
	}
	if (ft_strcmp(direction, "up") == 0)
	{
		data->offset.y -= TILE_SIZE;
		data->map.player_tile_position.y++;
		data->map.player_position.y += TILE_SIZE;
	}
	data->current_moves++;
	ft_printf("Current Moves: %d\n", data->current_moves);
}
