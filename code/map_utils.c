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

static void	get_map_size(t_data *data)
{
	int		fd;
	int		len;
	int		max_len;
	char	*line;

	max_len = 0;
	fd = open(data->map.path, O_RDONLY);
	if (fd < 0)
		ft_puterror("Error opening the map", data);
	data->map.size.y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		len = strlen(line);
		if (len > max_len)
			max_len = len;
		data->map.size.y++;
		free(line);
	}
	data->map.size.x = max_len * TILE_SIZE;
	close(fd);
}

static	void	set_player(t_data *data, int y, char *line, char *e)
{
	t_position	player_pos;

	player_pos.y = y * TILE_SIZE + 16;
	player_pos.x = ((int)(e - line) * TILE_SIZE) + 16;
	set_player_pos(data, player_pos);
	data->offset.x = (data->win_size / 2) - player_pos.x;
	data->offset.y = (data->win_size / 2) - player_pos.y;
}

static void	set_exit(t_data *data, int y, char *line, char *e)
{
	t_position	exit_pos;

	exit_pos.x = (int)(e - line);
	exit_pos.y = y;
	data->exit_position = exit_pos;
}

int get_map_measurements(t_data *data)
{
	int		fd;
	int		i;
	char	*line;
	char	*e;

	get_map_size(data);
	i = 0;
	data->map.map = malloc(sizeof(char *) * (data->map.size.y + 1));
	if (!data->map.map)
		ft_puterror("Error allocating the map.", data);
	fd = open(data->map.path, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!line)
			return (0);
		data->map.map[i] = ft_strdup(line);
		if ((e = strchr(line, 'P')))
			set_player(data, i, line, e);
		if ((e = strchr(line, 'E')))
			set_exit(data, i, line, e);
		if ((e = strchr(line, 'C')))
		{
			e = line;
			while ((e = strchr(e, 'C')) != NULL)
			{
				t_position *col = malloc(sizeof(t_position));
				if (!col)
					return (0);
				col->x = (int)(e - line);
				col->y = i;
				add_collectible(data, *col);
				e++;
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
