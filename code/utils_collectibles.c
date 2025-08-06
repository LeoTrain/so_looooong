/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_collectibles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:44:55 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 21:14:54 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int count_collectible(t_data *data)
{
	char	*line;
	int		i;
	int		count;

	data->current_fd = open(data->map.path, O_RDONLY);
	if (data->current_fd < 0)
		return (2001);
	count = 0;
	while ((line = get_next_line(data->current_fd)) != NULL)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == 'C')
				count++;
			i++;
		}
		free(line);
	}
	close(data->current_fd);
	data->current_fd = 0;
	return (count);
}

void add_collectible(t_data *data, t_position pos)
{
	t_collectible new_collectible;

	new_collectible.position = pos;
	new_collectible.collected = 0;
	if (!data->collectibles.collectibles)
		exit_error("No collectible initialized.", data);
	data->collectibles.collectibles[data->collectibles.count] = new_collectible;
	data->collectibles.count++;
}

int is_all_collectibles_collected(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map.tile_size.y)
	{
		x = 0;
		while (x < data->map.tile_size.x)
		{
			if (data->map.map[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	is_on_collectible(t_data *data)
{
	int	i;

	i = 0;
	if (data->map.map[data->map.player_position.y][data->map.player_position.x] == 'C')
	{
		while (i < data->collectibles.count)
		{
			if (is_same(data->collectibles.collectibles[i].position, data->map.player_position))
			{
				data->map.map[data->map.player_position.y][data->map.player_position.x] = '0';
				data->collectibles.collectibles[i].collected = 1;
			}
			i++;
		}
		return (1);
	}
	return (0);
}

void	create_collectibles(t_data *data)
{
	int collectible_amount;

	collectible_amount = count_collectible(data);
	if (collectible_amount == 2001)
		exit_error("Error\nopening the map. Does the file exist ?", data);
	if (collectible_amount == 0)
		exit_error("Error\nno collectibles found or count failed.", data);
	data->collectibles.collectibles = calloc(collectible_amount, sizeof(t_collectible));
	if (!data->collectibles.collectibles)
		exit_error("Error\ncalloc for collectibles failed.", data);
	data->collectibles.count = 0;
}
