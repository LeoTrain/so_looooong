/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:00:00 by leberton          #+#    #+#             */
/*   Updated: 2025/08/06 20:13:37 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_image(void *mlx, void **img, char *path, t_position size)
{
	*img = mlx_xpm_file_to_image(mlx, path, &size.x, &size.y);
	if (!*img)
		return (0);
	return (1);
}

static void	draw_at_pos(t_data *data, t_position curr_pos, t_position curr_tile)
{
	if (data->map.map[curr_tile.y][curr_tile.x] == '1')
		mlx_put_image_to_window(data->mlx, data->win, data->assets.wall.img,
			curr_pos.x, curr_pos.y);
	else if (data->map.map[curr_tile.y][curr_tile.x] == '0' ||
			data->map.map[curr_tile.y][curr_tile.x] == 'P')
		mlx_put_image_to_window(data->mlx, data->win, data->assets.grass.img,
			curr_pos.x, curr_pos.y);
	else if (data->map.map[curr_tile.y][curr_tile.x] == 'C')
		mlx_put_image_to_window(data->mlx, data->win,
			data->assets.collectible.img, curr_pos.x, curr_pos.y);
	else if (data->map.map[curr_tile.y][curr_tile.x] == 'E')
		mlx_put_image_to_window(data->mlx, data->win, data->assets.exit.img,
			curr_pos.x, curr_pos.y);
}

static void	draw_moves(t_data *data)
{
	char	*moves_str;

	moves_str = ft_itoa(data->current_moves);
	if (!moves_str)
		return ;
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, moves_str);
	free(moves_str);
}

void	draw(t_data *data)
{
	t_position	half_win_size;
	t_position	current_tile;
	t_position	current_pos;

	mlx_clear_window(data->mlx, data->win);
	current_tile.y = 0;
	while (current_tile.y < data->map.tile_size.y)
	{
		current_tile.x = 0;
		while (current_tile.x < data->map.tile_size.x)
		{
			current_pos.x = (current_tile.x * TILE_SIZE) + data->offset.x;
			current_pos.y = (current_tile.y * TILE_SIZE) + data->offset.y;
			draw_at_pos(data, current_pos, current_tile);
			current_tile.x++;
		}
		current_tile.y++;
	}
	half_win_size.x = (data->win_width / 2) - TILE_SIZE;
	half_win_size.y = (data->win_height / 2) - TILE_SIZE;
	mlx_put_image_to_window(data->mlx, data->win, data->assets.character.img,
		half_win_size.x, half_win_size.y);
	draw_moves(data);
}
