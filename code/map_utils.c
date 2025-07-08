/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:34:31 by leberton          #+#    #+#             */
/*   Updated: 2025/07/08 19:56:21 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int get_map_measurements(t_data *data)
{
	int fd;
	char *line;
	char *e;
	int i = 0;
	size_t max_len = 0;

	fd = open(data->map.path, O_RDONLY);
	if (fd < 0)
		return (0);

	data->map.size.y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		size_t len = strlen(line);
		if (len > max_len)
			max_len = len;
		data->map.size.y++;
		free(line);
	}
	data->map.size.x = max_len * TILE_SIZE;
	close(fd);

	data->map.map = malloc(sizeof(char *) * (data->map.size.y + 1));
	if (!data->map.map)
		return (0);
	fd = open(data->map.path, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!line)
			return (0);
		data->map.map[i] = ft_strdup(line);
		if ((e = strchr(line, 'P')))
		{
			int player_pos_y = i * TILE_SIZE + 16;
			int player_pos_x = ((int)(e - line) * TILE_SIZE) + 16;
			data->offset.x = (data->win_size / 2) - player_pos_x;
			data->offset.y = (data->win_size / 2) - player_pos_y;
		}
		if ((e = strchr(line, 'E')))
			data->exit_position = (t_position){(int)(e - line), i};
		if ((e = strchr(line, 'C')))
		{
			char *pos = line;
			while ((pos = strchr(pos, 'C')) != NULL)
			{
				t_position *col = malloc(sizeof(t_position));
				if (!col)
					return (0);
				col->x = (int)(pos - line);
				col->y = i;
				add_collectible(data, *col);
				pos++;
				free(col);
			}
		}
		i++;
		free(line);
	}
	data->map.map[i] = NULL;
	data->map.size.y *= TILE_SIZE;
	close(fd);
	return (1);
}
