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

int count_coullectible(t_data *data)
{
	int		count;
	char	*line;
	int		i;

	count = 0;
	data->current_fd = open(data->map.path, O_RDONLY);
	if (data->current_fd < 0)
		return (2001);
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
	for (int i = 0; i < data->map.size.y / TILE_SIZE; i++)
	{
		for (int j = 0; j < data->map.size.x / TILE_SIZE; j++)
		{
			if (data->map.map[i][j] == 'C')
				return (0);
		}
	}
	return (1);
}

int	is_on_collectible(t_data *data)
{
	int	i;

	get_player_pos(data);
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

