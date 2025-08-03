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
	int		fd;
	char	*line;
	int		i;

	count = 0;
	fd = open(data->map.path, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)) != NULL)
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
	close(fd);
	return (count);
}

void add_collectible(t_data *data, t_position pos)
{
	t_collectible new_collectible;

	new_collectible.position = pos;
	new_collectible.collected = false;
	if (!data->collectibles.collectibles)
		exit_error("No collectible initialized.", data);
	data->collectibles.collectibles[data->collectibles.count] = new_collectible;
	data->collectibles.count++;
}

void	sort_collectibles(t_data *data)
{
	t_position		current_pos;
	t_position		next_pos;
	t_collectible	temp;
	
	if (!data->collectibles.collectibles)
		return ;
	current_pos = data->collectibles.collectibles[0].position;
	while (1)
	{
		int swapped = 0;
		for (int i = 0; i < data->collectibles.count - 1; i++)
		{
			current_pos = data->collectibles.collectibles[i].position;
			next_pos = data->collectibles.collectibles[i + 1].position;
			if (current_pos.y > next_pos.y ||
				(current_pos.y == next_pos.y && current_pos.x > next_pos.x))
			{
				temp = data->collectibles.collectibles[i];
				data->collectibles.collectibles[i] = data->collectibles.collectibles[i + 1];
				data->collectibles.collectibles[i + 1] = temp;
				swapped = 1;
			}
		}
		if (!swapped)
			break;
	}
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
				data->collectibles.collectibles[i].collected = true;
			}
			i++;
		}
		return (1);
	}
	return (0);
}

