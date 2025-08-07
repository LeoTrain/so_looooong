/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:57:53 by leberton          #+#    #+#             */
/*   Updated: 2025/08/07 17:29:29 by leberton         ###   ########.fr       */
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

int	is_tile_free(t_data *data, int x, int y)
{
	t_position	pos;

	pos.x = x;
	pos.y = y;
	if (is_not_in_border(data, pos))
		return (0);
	if (data->map.map[y][x] == '1')
		return (0);
	return (1);
}

static void	try_move_enemy(t_data *data, t_position *enemy, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_y = enemy->y + dy;
	new_x = enemy->x + dx;
	if (is_tile_free(data, new_x, new_y))
	{
		enemy->x = new_x;
		enemy->y = new_y;
	}
}

static void	try_move(t_data *data, t_position *enem, t_position s_enem,
	t_position dir)
{
	if (abs(dir.x) > abs(dir.y))
	{
		try_move_enemy(data, enem, (dir.x > 0) - (dir.x < 0), 0);
		if (enem->x == s_enem.x)
			try_move_enemy(data, enem, 0, (dir.y > 0) - (dir.y < 0));
	}
	else
	{
		try_move_enemy(data, enem, 0, (dir.y > 0) - (dir.y < 0));
		if (enem->y == s_enem.y)
			try_move_enemy(data, enem, (dir.x > 0) - (dir.x < 0), 0);
	}
}

void	track_player(t_data *data)
{
	t_position	start_enemy;
	t_position	*enemy;
	t_position	player;
	t_position	d;

	start_enemy = data->map.enemy_tile_position;
	enemy = &data->map.enemy_tile_position;
	player = data->map.player_tile_position;
	d.x = player.x - enemy->x;
	d.y = player.y - enemy->y;
	if (!data->is_enemy_set)
		return ;
	try_move(data, enemy, start_enemy, d);
}
