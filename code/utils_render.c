/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:00:00 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 19:35:44 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	void	draw_asset(t_data *data, t_position current_pos, char *asset)
{
	if (ft_strcmp(asset, "wall") == 0)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->assets.wall.img, current_pos.x, current_pos.y);
		return ;
	}
	if (ft_strcmp(asset, "grass") == 0)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->assets.grass.img, current_pos.x, current_pos.y);
		return ;
	}
	if (ft_strcmp(asset, "collectible") == 0)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->assets.collectible.img, current_pos.x, current_pos.y);
		return ;
	}
	if (ft_strcmp(asset, "exit") == 0)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->assets.exit.img, current_pos.x, current_pos.y);
		return ;
	}
}

static t_bool	is_asset(t_data *data, t_position current_tile, char *asset)
{
	if (ft_strcmp(asset, "wall") == 0)
		return (data->map.map[current_tile.y][current_tile.x] == '1');
	if (ft_strcmp(asset, "grass") == 0)
		return (data->map.map[current_tile.y][current_tile.x] == '0' ||
				data->map.map[current_tile.y][current_tile.x] == 'P');
	if (ft_strcmp(asset, "collectible") == 0)
		return (data->map.map[current_tile.y][current_tile.x] == 'C');
	if (ft_strcmp(asset, "exit") == 0)
		return (data->map.map[current_tile.y][current_tile.x] == 'E');
	return (false);
}

static void	draw_at_pos(t_data *data, t_position current_pos, t_position current_tile)
{
	if (is_asset(data, current_tile, "wall"))
		draw_asset(data, current_pos, "wall");
	else if (is_asset(data, current_tile, "grass"))
		draw_asset(data, current_pos, "grass");
	else if (is_asset(data, current_tile, "collectible"))
		draw_asset(data, current_pos, "collectible");
	else if (is_asset(data, current_tile, "exit"))
		draw_asset(data, current_pos, "exit");
}

static void	draw_moves(t_data *data)
{
	char *moves_str;

	moves_str = ft_itoa(data->current_moves);
	if (!moves_str)
		return ;
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, moves_str);
	free(moves_str);
}

void	draw(t_data *data)
{
	int			half_win_size;
	t_position	current_tile;
	t_position	current_pos;

	mlx_clear_window(data->mlx, data->win);
	current_tile.y = 0;
	while (data->map.map[current_tile.y])
	{
		current_tile.x = 0;
		while (current_tile.x < (int)ft_strlen(data->map.map[current_tile.y]))
		{
			current_pos.x = (current_tile.x * TILE_SIZE) + data->offset.x;
			current_pos.y = (current_tile.y * TILE_SIZE) + data->offset.y;
			draw_at_pos(data, current_pos, current_tile);
			current_tile.x++;
		}
		current_tile.y++;
	}
	half_win_size = (data->win_size / 2) - TILE_SIZE;
	mlx_put_image_to_window(data->mlx, data->win, data->assets.character.img, half_win_size, half_win_size);
	draw_moves(data);
}
