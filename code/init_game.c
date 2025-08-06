/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:29:10 by leberton          #+#    #+#             */
/*   Updated: 2025/08/06 21:06:07 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit_error("Error\ncreating the mlx variable.", data);
	data->win_width = 640;
	data->win_height = 360;
	data->win = mlx_new_window(data->mlx, data->win_width, data->win_height, "Test1");
	if (!data->win)
		exit_error("Error\ncreating the window.", data);
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
	data->map.exit_position.x = -1;
	data->map.exit_position.y = -1;
	create_collectibles(data);
	get_map_measurements(data);
}

static void	init_data(t_data *data, char *map_path)
{
	data->found_collectible = -1;
	data->found_exit = -1;
	data->is_player_set = -1;
	data->is_exit_set = -1;
	data->current_fd = -1;
	data->current_moves = 0;
	init_mlx(data);
	init_assets(data);
	init_map(data, map_path);
}

void	init_game(t_data *data, char *map_path)
{
	init_data(data, map_path);
	is_makeable(data);
}
