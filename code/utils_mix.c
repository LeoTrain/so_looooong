/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:59:18 by leberton          #+#    #+#             */
/*   Updated: 2025/08/06 20:07:46 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

long	get_time_in_ms(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return (timev.tv_sec * 1000 + timev.tv_usec / 1000);
}

int	is_same(t_position a, t_position b)
{
	return (a.x == b.x && a.y == b.y);
}

void	set_player_pos(t_data *data, t_position pos)
{
	data->map.player_tile_position.x = pos.x;
	data->map.player_tile_position.y = pos.y;
	data->map.player_position.x = pos.x * TILE_SIZE + TILE_SIZE;
	data->map.player_position.y = (pos.y * TILE_SIZE) + TILE_SIZE;
}

void	load_all_images(t_data *data)
{
	if (!load_image(data->mlx, (void **)&data->assets.character.img,
			data->assets.character.path, data->map.tile_size))
		exit_error("Error\nloading the character image.", data);
	if (!load_image(data->mlx, (void **)&data->assets.enemy.img,
			data->assets.enemy.path, data->map.tile_size))
		exit_error("Error\nloading the character image.", data);
	if (!load_image(data->mlx, (void **)&data->assets.grass.img,
			data->assets.grass.path, data->map.tile_size))
		exit_error("Error\nloading the grass image.", data);
	if (!load_image(data->mlx, (void **)&data->assets.wall.img,
			data->assets.wall.path, data->map.tile_size))
		exit_error("Error\nloading the wall image.", data);
	if (!load_image(data->mlx, (void **)&data->assets.collectible.img,
			data->assets.collectible.path, data->map.tile_size))
		exit_error("Error\nloading the collectible image.", data);
	if (!load_image(data->mlx, (void **)&data->assets.exit.img,
			data->assets.exit.path, data->map.tile_size))
		exit_error("Error\nloading the exit image.", data);
}
