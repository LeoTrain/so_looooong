/* ************************************************************************** */
/*                                                                            */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                        :::      ::::::::   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:34:07 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 18:51:44 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_images(t_data *data)
{
	if (data->assets.character.img)
		mlx_destroy_image(data->mlx, data->assets.character.img);
	if (data->assets.grass.img)
		mlx_destroy_image(data->mlx, data->assets.grass.img);
	if (data->assets.wall.img)
		mlx_destroy_image(data->mlx, data->assets.wall.img);
	if (data->assets.collectible.img)
		mlx_destroy_image(data->mlx, data->assets.collectible.img);
	if (data->assets.exit.img)
		mlx_destroy_image(data->mlx, data->assets.exit.img);
}

static void	free_map(t_data *data, int and_map)
{
	int	i;

	i = 0;
	while (data->map.map_is_makeable && i < (data->map.size.y / TILE_SIZE) + 1)
		free(data->map.map_is_makeable[i++]);
	free(data->map.map_is_makeable);
	i = 0;
	while (data->map.map && i < (data->map.size.y / TILE_SIZE) + 1)
		free(data->map.map[i++]);
	free(data->map.map);
	if (data->map.path && and_map)
		free(data->map.path);
}

static void	free_mlx(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	free_all(t_data *data)
{
	free_images(data);
	free_map(data, 1);
	free_mlx(data);
	free(data->collectibles.collectibles);
	if (data->current_fd != 0)
	{
		close(data->current_fd);
		data->current_fd = 0;
	}
}
