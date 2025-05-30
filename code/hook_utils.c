/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:44:56 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 17:12:09 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw(t_data *data)
{

	mlx_clear_window(data->mlx, data->win);
	int i = 0;
	int y = 0;
	while (data->map.map[y])
	{
		for (i = 0; i < data->map.size.x; i++)
		{
			int pos_x = (TILE_SIZE * i) + data->offset.x;
			int pos_y = (y * TILE_SIZE) + data->offset.y;
			if (data->map.map[y][i] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->assets.wall.img, pos_x, pos_y);
			else if (data->map.map[y][i] == '0')
				mlx_put_image_to_window(data->mlx, data->win, data->assets.grass.img, pos_x, pos_y);
			else if (data->map.map[y][i] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->assets.collectible.img, pos_x, pos_y);
		}
		y++;
	}
	int player_pos_y = (data->win_size / 2) - 16;
	int player_pos_x = (data->win_size / 2) - 16;
	mlx_put_image_to_window(data->mlx, data->win, data->assets.character.img, player_pos_x, player_pos_y);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 119 && !is_next_tile_wall(data, 0, -1))
		data->offset.y += TILE_SIZE;
	else if (keycode == 115 && !is_next_tile_wall(data, 0, 1))
		data->offset.y -= TILE_SIZE;
	else if (keycode == 97 && !is_next_tile_wall(data, -1, 0))
		data->offset.x += TILE_SIZE;
	else if (keycode == 100 && !is_next_tile_wall(data, 1, 0))
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
		move_to_collectible(data, data->collectible_list.collectibles);
		if (is_on_collectible(data))
			printf("You collected collectibles!\n");
	}
	return (0);
}
