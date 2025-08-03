/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:34:07 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 18:51:44 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "so_long.h"

void	free_images(t_data *data)
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

void	free_map(t_data *data)
{
	int	i;

	if (data->map.map && data->map.visited)
	{
		i = 0;
		while (data->map.map[i])
		{
			free(data->map.map[i]);
			free(data->map.visited[i++]);
		}
		free(data->map.map);
		free(data->map.visited);
	}
	if (data->map.path)
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
	free_map(data);
	free_mlx(data);
	free(data->collectibles.collectibles);
}
