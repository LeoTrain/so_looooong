/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_question.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:40:38 by leberton          #+#    #+#             */
/*   Updated: 2025/08/07 17:12:05 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_not_in_border(t_data *data, t_position next)
{
	if (next.x < 0 || next.x >= data->map.tile_size.x)
		return (1);
	if (next.y < 0 || next.y >= data->map.tile_size.y)
		return (1);
	return (0);
}

static int	is_wall(t_data *data, t_position pos)
{
	return (data->map.map[pos.y][pos.x] == '1');
}

int	is_next_tile_wall(t_data *data, int x, int y)
{
	t_position	next;

	next.x = data->map.player_tile_position.x + x;
	next.y = data->map.player_tile_position.y + y;
	return (is_not_in_border(data, next) || is_wall(data, next));
}

int	is_on_exit(t_data *data)
{
	return (is_same(data->map.player_tile_position, data->map.exit_position));
}
