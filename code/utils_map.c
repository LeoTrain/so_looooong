/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:34:31 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 21:17:42 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	is_rectangular(t_data *data)
{
	char	**p_map;
	size_t	last_length;

	last_length = 0;
	p_map = data->map.map;
	while (*p_map)
	{
		if (!last_length)
			last_length = ft_strlen(*p_map);
		else if (ft_strlen(*p_map) != last_length)
			exit_error("Error\nMap not rectangular.\n", data);
		p_map++;
	}
}

static void	is_surrounded_by_wall(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (data->map.map)
	{
		while (y < data->map.tile_size.y)
		{
			if (data->map.map[y][0] != '1' || data->map.map[y][data->map.tile_size.x - 1] != '1')
			{
				ft_printf("Wall at y == %d = %c or %c\n", y, data->map.map[y][0], data->map.map[y][data->map.tile_size.x - 1]);
				exit_error("Error\nmap is not surrounded by walls.\n", data);
			}
			y++;
		}
		while (x < data->map.tile_size.x)
		{
			if (data->map.map[0][x] != '1' || data->map.map[data->map.tile_size.y - 1][x] != '1')
				exit_error("Error\nmap is not surrounded by walls.\n", data);
			x++;
		}
	}
}

void	get_map_measurements(t_data *data)
{
	get_map_size(data);
	allocate_for_map(data);
	parse_map(data);
	is_rectangular(data);
	is_surrounded_by_wall(data);
}
