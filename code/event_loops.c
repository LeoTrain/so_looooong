/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_loops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:44:56 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 21:10:18 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	exec_actions(t_data *data)
{
	if (is_on_collectible(data))
		return ;
	if (is_on_exit(data))
	{
		if (is_all_collectibles_collected(data) == 0)
			return ;
		exit_success("Player is on exit, quitting...", data);
	}
}

static void	react_uppon_keycode(t_data *data, int keycode)
{
	if (keycode == 65307 || keycode == 53)
		exit_success("Player pressed ESC, quitting...", data);
	if ((keycode == 119 || keycode == 13) && !is_next_tile_wall(data, stand, down))
		move("down", data);
	else if ((keycode == 115 || keycode == 1) && !is_next_tile_wall(data, stand, up))
		move("up", data);
	else if ((keycode == 97 || keycode == 0) && !is_next_tile_wall(data, left, stand))
		move("left", data);
	else if ((keycode == 100 || keycode == 2) && !is_next_tile_wall(data, right, stand))
		move("right", data);
}

int	key_hook(int keycode, t_data *data)
{
	react_uppon_keycode(data, keycode);
	exec_actions(data);
	return (0);
}

int	loop_hook(t_data *data)
{
	static long	last_time;
	long		current_time;

	if (last_time == 0)
		last_time = get_time_in_ms();
	current_time = get_time_in_ms();
	if (current_time - last_time >= 200)
	{
		last_time = current_time;
		exec_actions(data);
		// if (!data->moving)
		// 	move_to_collectible(data, data->collectibles.collectibles);
		// else
		// 	move_player_path(data);
		draw(data);
	}
	return (0);
}
