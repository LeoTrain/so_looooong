/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:00:00 by leberton          #+#    #+#             */
/*   Updated: 2025/06/03 22:02:41 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw(t_data *data)
{

	mlx_clear_window(data->mlx, data->win);
	int i = 0;
	int y = 0;
	while (data->map.map[y])
	{
		for (i = 0; i < (int)strlen(data->map.map[y]); i++)
		{
			int pos_x = (TILE_SIZE * i) + data->offset.x;
			int pos_y = (y * TILE_SIZE) + data->offset.y;
			if (data->map.map[y][i] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->assets.wall.img, pos_x, pos_y);
			else if (data->map.map[y][i] == '0')
				mlx_put_image_to_window(data->mlx, data->win, data->assets.grass.img, pos_x, pos_y);
			else if (data->map.map[y][i] == 'C')
				mlx_put_image_to_window(data->mlx, data->win, data->assets.collectible.img, pos_x, pos_y);
			else if (data->map.map[y][i] == 'E')
				mlx_put_image_to_window(data->mlx, data->win, data->assets.exit.img, pos_x, pos_y);
		}
		y++;
	}
	int player_pos_y = (data->win_size / 2) - TILE_SIZE;
	int player_pos_x = (data->win_size / 2) - TILE_SIZE;
	mlx_put_image_to_window(data->mlx, data->win, data->assets.character.img, player_pos_x, player_pos_y);
}

