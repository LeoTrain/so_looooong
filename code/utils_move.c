/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:33:15 by leberton          #+#    #+#             */
/*   Updated: 2025/08/07 11:35:18 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_left(t_data *data)
{
	data->offset.x += TILE_SIZE;
	data->map.player_tile_position.x--;
	data->map.player_position.x -= TILE_SIZE;
}

static void	move_right(t_data *data)
{
	data->offset.x -= TILE_SIZE;
	data->map.player_tile_position.x++;
	data->map.player_position.x += TILE_SIZE;
}

static void	move_down(t_data *data)
{
	data->offset.y += TILE_SIZE;
	data->map.player_tile_position.y--;
	data->map.player_position.y -= TILE_SIZE;
}

static void	move_up(t_data *data)
{
	data->offset.y -= TILE_SIZE;
	data->map.player_tile_position.y++;
	data->map.player_position.y += TILE_SIZE;
}

void	move(char *direction, t_data *data)
{
	if (ft_strcmp(direction, "left") == 0)
		move_left(data);
	if (ft_strcmp(direction, "right") == 0)
		move_right(data);
	if (ft_strcmp(direction, "down") == 0)
		move_down(data);
	if (ft_strcmp(direction, "up") == 0)
		move_up(data);
	data->current_moves++;
	ft_printf("Current Moves: %d\n", data->current_moves);
}
