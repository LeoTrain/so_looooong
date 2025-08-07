/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_enemy_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:27:35 by leberton          #+#    #+#             */
/*   Updated: 2025/08/07 17:32:03 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_enemy(t_data *data)
{
	t_position	pixel_pos;
	t_position	pos;

	pos = data->map.enemy_tile_position;
	pixel_pos.x = (pos.x * TILE_SIZE) + data->offset.x;
	pixel_pos.y = (pos.y * TILE_SIZE) + data->offset.y;
	mlx_put_image_to_window(data->mlx, data->win, data->assets.enemy.img,
		pixel_pos.x, pixel_pos.y);
}

void	draw_caught_message(t_data *data)
{
	if (data->is_player_caught)
		mlx_string_put(data->mlx, data->win,
			data->win_width / 2 - 100,
			data->win_height / 2,
			0xFFFFFF, "The enemy caught you! Press <ESC> to exit.");
}

void	set_enemy(t_data *data, int y, char *line, char *e)
{
	t_position	enemy_pos;

	if (data->is_enemy_set == 1 || is_another_on_line('X', line))
	{
		free_current_map(data, y);
		exit_error("Error\ntoo many enemy positions.", data);
	}
	data->found_exit = 1;
	enemy_pos.x = (int)(e - line);
	enemy_pos.y = y;
	data->is_enemy_set = 1;
	data->map.enemy_tile_position = enemy_pos;
}
