/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:35:02 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 21:06:58 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_all_images(t_data *data)
{
	if (!load_image(data->mlx, (void **)&data->assets.character.img, data->assets.character.path, &data->map.tile_size.x, &data->map.tile_size.y))
		exit_error("Error\nloading the character image.", data);
	if (!load_image(data->mlx, (void **)&data->assets.grass.img, data->assets.grass.path, &data->map.tile_size.x, &data->map.tile_size.y))
		exit_error("Error\nloading the grass image.", data);
	if (!load_image(data->mlx, (void **)&data->assets.wall.img, data->assets.wall.path, &data->map.tile_size.x, &data->map.tile_size.y))
		exit_error("Error\nloading the wall image.", data);
	if (!load_image(data->mlx, (void **)&data->assets.collectible.img, data->assets.collectible.path, &data->map.tile_size.x, &data->map.tile_size.y))
		exit_error("Error\nloading the collectible image.", data);
	if (!load_image(data->mlx, (void **)&data->assets.exit.img, data->assets.exit.path, &data->map.tile_size.x, &data->map.tile_size.y))
		exit_error("Error\nloading the exit image.", data);
}

void	create_collectibles(t_data *data)
{
	int collectible_amount;

	collectible_amount = count_coullectible(data);
	if (collectible_amount <= 0)
		exit_error("Error\nno collectibles found or count failed.", data);
	data->collectibles.collectibles = calloc(collectible_amount, sizeof(t_collectible));
	if (!data->collectibles.collectibles)
		exit_error("Error\ncalloc for collectibles failed.", data);
	data->collectibles.count = 0;
}

void	free_current_visited(t_data *data, int i)
{
	while (--i >= 0)
		free(data->map.visited[i]);
	free(data->map.visited);
	exit_error("Error creating visited row.", data);
}

void	allocate_visited_array_row(t_data *data, t_position map_tile_size)
{
	int	i;

	i = 0;
	while (i < map_tile_size.y)
	{
		data->map.visited[i] = ft_calloc(map_tile_size.x, sizeof(t_bool));
		if (!data->map.visited[i])
			free_current_visited(data, i);
		i++;
	}
}

void	create_visited(t_data *data)
{
	t_position	map_tile_size;

	map_tile_size.y = data->map.size.y / TILE_SIZE;
	data->map.visited = malloc(map_tile_size.y * sizeof(t_bool *));
	if (!data->map.visited)
		exit_error("Error creating visited 1.", data);
	map_tile_size.x = data->map.size.x / TILE_SIZE;
	allocate_visited_array_row(data, map_tile_size);
}
