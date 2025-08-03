/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:29:10 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 20:42:49 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_puterror("Error: creating the mlx variable.\n", data);
	data->win_size = 800; //20 * TILE_SIZE;
	data->win = mlx_new_window(data->mlx, data->win_size, data->win_size, "Test1");
	if (!data->win)
		ft_puterror("Error: creating the window.\n", data);
}

static void	init_assets(t_data *data)
{
	data->assets.character.path = "assets/xpm/64x/normal_amazed.xpm";
	data->assets.grass.path = "assets/xpm/64x/empty_space.xpm";
	data->assets.wall.path = "assets/xpm/64x/wall.xpm";
	data->assets.collectible.path = "assets/xpm/64x/collectible.xpm";
	data->assets.exit.path = "assets/xpm/64x/exit.xpm";
	load_all_images(data);
}

static void	init_map(t_data *data, char *map_path)
{
	data->map.path = ft_strdup(map_path);
	data->map.exit_position = (t_position){-1, -1};
	create_collectibles(data);
	if (!get_map_measurements(data))
		ft_puterror("Error\nreading the map file.\n", data);
	create_visited(data);
	get_player_pos(data);
}

void	init_game(t_data *data, char *map_path)
{
	init_mlx(data);
	init_assets(data);
	init_map(data, map_path);
	is_makeable(data);
}
