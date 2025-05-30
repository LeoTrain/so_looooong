/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:34:31 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 14:34:50 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_measurements(t_data *data)
{
	int		fd;
	char	*line;
	char	*e;
	int		i = 0;

	fd = open(data->map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	data->map_height = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		data->map_height++;
		free(line);
	}
	close(fd);
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
		return (0);
	fd = open(data->map_path, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		data->map[i] = ft_strdup(line);
		if ((e = strchr(line, 'P')))
		{
			int player_pos_y = i * TILE_SIZE + 16;
			int player_pos_x = ((int)(e - line) * TILE_SIZE) + 16;
			data->x_offset = (data->win_size / 2) - player_pos_x;
			data->y_offset = (data->win_size / 2) - player_pos_y;
		}
		if ((e = strchr(line, 'E')) && !data->exit_pos)
		{
			data->exit_pos = (int *)calloc(2, sizeof(int));
			data->exit_pos[0] = i;
			data->exit_pos[1] = (int)(e - line);
		}
		if ((e = strchr(line, 'C')))
		{
			char *pos = line;
			while ((pos = strchr(pos, 'C')) != NULL)
			{
				t_position *col = malloc(sizeof(t_position));
				if (!col)
					return (0);
				col->x = i;
				col->y = (int)(pos - line);
				t_list *new_collectible = ft_lstnew(col);
				ft_lstadd_front(&data->collectibles, new_collectible);
				pos++;
				data->collectibles_total++;
			}
		}
		i++;
		data->map_width = strlen(line) * TILE_SIZE;
		free(line);
	}
	data->map[i] = NULL;
	data->map_height *= TILE_SIZE;
	close(fd);
	return (1);
}
