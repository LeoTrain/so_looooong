/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:44:56 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 14:46:02 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw(t_data *data)
{

	mlx_clear_window(data->mlx, data->win);
	int i = 0;
	int row = 0;
	while (data->map[row])
	{
		for (i = 0; i < data->map_width; i++)
		{
			int pos_x = (TILE_SIZE * i) + data->x_offset;
			int pos_y = (row * TILE_SIZE) + data->y_offset;
			if (data->map[row][i] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->wall_img, pos_x, pos_y);
			else if (data->map[row][i] == '0')
				mlx_put_image_to_window(data->mlx, data->win, data->grass_img, pos_x, pos_y);
			else if (data->map[row][i] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->collectible_img, pos_x, pos_y);
		}
		row++;
	}
	int player_pos_y = (data->win_size / 2) - 16;
	int player_pos_x = (data->win_size / 2) - 16;
	mlx_put_image_to_window(data->mlx, data->win, data->character_img, player_pos_x, player_pos_y);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 119 && !is_next_tile_wall(data, 0, -1))
		data->y_offset += TILE_SIZE;
	else if (keycode == 115 && !is_next_tile_wall(data, 0, 1))
		data->y_offset -= TILE_SIZE;
	else if (keycode == 97 && !is_next_tile_wall(data, -1, 0))
		data->x_offset += TILE_SIZE;
	else if (keycode == 100 && !is_next_tile_wall(data, 1, 0))
		data->x_offset -= TILE_SIZE;
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
	{
		printf("You collected %d collectibles!\n", data->collected_collectibles);
	}
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
		move_to_collectible(data, data->collectibles);
	}
	return (0);
}
