/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:29:10 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 18:54:47 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_bool	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error: creating the mlx variable.\n");
		return (false);
	}
	data->win_size = 20 * TILE_SIZE;
	data->win = mlx_new_window(data->mlx, data->win_size, data->win_size, "Test1");
	if (!data->win)
	{
		printf("Error: creating the window.\n");
		return (false);
	}
	return (1);
}

static t_bool	init_assets(t_data *data)
{
	data->assets.character.path = "assets/xpm/64x/normal_amazed.xpm";
	data->assets.grass.path = "assets/xpm/64x/empty_space.xpm";
	data->assets.wall.path = "assets/xpm/64x/wall.xpm";
	data->assets.collectible.path = "assets/xpm/64x/collectible.xpm";
	data->assets.exit.path = "assets/xpm/64x/exit.xpm";
	if (!load_image(data->mlx, (void **)&data->assets.character.img, data->assets.character.path, &data->map.tile_size.x, &data->map.tile_size.y)
		|| !load_image(data->mlx, (void **)&data->assets.grass.img, data->assets.grass.path, &data->map.tile_size.x, &data->map.tile_size.y)
		|| !load_image(data->mlx, (void **)&data->assets.wall.img, data->assets.wall.path, &data->map.tile_size.x, &data->map.tile_size.y)
		|| !load_image(data->mlx, (void **)&data->assets.collectible.img, data->assets.collectible.path, &data->map.tile_size.x, &data->map.tile_size.y)
		|| !load_image(data->mlx, (void **)&data->assets.exit.img, data->assets.exit.path, &data->map.tile_size.x, &data->map.tile_size.y))
	{
		printf("Error: loading one or more images.\n");
		return (false);
	}
	return (true);
}

static t_bool	init_collectibles(t_data *data)
{
	int nb;

	nb = count_coullectible(data);
	if (nb <= 0)
		ft_puterror("Error: no collectibles found or count failed.", data);
	data->collectibles.collectibles = calloc(nb, sizeof(t_collectible));
	if (!data->collectibles.collectibles)
		ft_puterror("Error: calloc for collectibles failed.", data);
	data->collectibles.count = 0;
	return (true);
}

static void	init_visited(t_data *data)
{
	t_position	map_tile_size;
	int			i;

	map_tile_size.y = data->map.size.y / TILE_SIZE;
	data->map.visited = malloc(map_tile_size.y * sizeof(t_bool *));
	if (!data->map.visited)
		ft_puterror("Error creating visited 1.", data);
	i = 0;
	map_tile_size.x = data->map.size.x / TILE_SIZE;
	while (i < map_tile_size.y)
	{
		data->map.visited[i] = ft_calloc(map_tile_size.x, sizeof(t_bool));
		if (!data->map.visited[i])
		{
			while (--i >= 0)
				free(data->map.visited[i]);
			free(data->map.visited);
			ft_puterror("Error creating visited 2.", data);
		}
		i++;
	}
}

static t_bool	init_map(t_data *data, char *map_path)
{
	data->map.path = ft_strdup(map_path);
	data->map.exit_position = (t_position){-1, -1};
	if (!init_collectibles(data))
		return (false);
	if (!get_map_measurements(data))
	{
		printf("Error: reading the map file.\n");
		return (false);
	}
	init_visited(data);
	get_player_pos(data);
	return (true);
}


t_bool	init_game(t_data *data, char *map_path)
{
	if (!init_mlx(data))
		return (1004);
	if (!init_assets(data))
		return (1003);
	if (!init_map(data, map_path))
		return (1002);
	is_makeable(data, data->map.player_position.x, data->map.player_position.y);
	if (data->found_collectible == data->collectibles.count && data->found_exit == 1)
		return (0);
	return (1);
}
