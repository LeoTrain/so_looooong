/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_loops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:44:56 by leberton          #+#    #+#             */
/*   Updated: 2025/06/03 22:03:18 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307 || keycode == 53)
		exit(0);
	if ((keycode == 119 || keycode == 13) && !is_next_tile_wall(data, 0, -1))
		data->offset.y += TILE_SIZE;
	else if ((keycode == 115 || keycode == 1) && !is_next_tile_wall(data, 0, 1))
		data->offset.y -= TILE_SIZE;
	else if ((keycode == 97 || keycode == 0) && !is_next_tile_wall(data, -1, 0))
		data->offset.x += TILE_SIZE;
	else if ((keycode == 100 || keycode == 2) && !is_next_tile_wall(data, 1, 0))
		data->offset.x -= TILE_SIZE;
	if (is_on_exit(data))
	{
		if (!is_all_collectibles_collected(data))
		{
			printf("You need to collect all collectibles before exiting!\n");
			return (0);
		}
		printf("You reached the exit!\n");
		exit(0);
	}
	if (is_on_collectible(data))
		printf("You collected collectibles!\n");
	return (0);
}

int	loop_hook(t_data *data)
{
	static long	last_time;
	long		current_time;

	if (last_time == 0)
		last_time = get_time_in_ms();
	current_time = get_time_in_ms();
	if (current_time - last_time >= 100)
	{
		last_time = current_time;
		draw(data);
		if (!data->moving)
			move_to_collectible(data, data->collectibles.collectibles);
		else
			move_player_path(data);
	}
	return (0);
}
