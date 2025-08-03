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

static void	get_map_size(t_data *data)
{
	int		fd;
	int		len;
	int		max_len;
	char	*line;

	max_len = 0;
	fd = open(data->map.path, O_RDONLY);
	if (fd < 0)
		exit_error("Error opening the map", data);
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

	player_pos.y = y * TILE_SIZE + TILE_SIZE;
	player_pos.x = ((int)(e - line) * TILE_SIZE) + TILE_SIZE;
	set_player_pos(data, player_pos);
	data->offset.x = (data->win_size / 2) - player_pos.x;
	data->offset.y = (data->win_size / 2) - player_pos.y;
}

static void	set_exit(t_data *data, int y, char *line, char *e)
{
	t_position	exit_pos;

	exit_pos.x = (int)(e - line);
	exit_pos.y = y;
	data->map.exit_position = exit_pos;
}

static void	set_collectible(t_data *data, int y, char *line)
{
	t_position	col;
	char		*e;

	e = line;
	while ((e = strchr(e, 'C')) != NULL)
	{
		col.x = (int)(e - line);
		col.y = y;
		add_collectible(data, col);
		e++;
	}
}

static void	parse_map_line(t_data *data, char *line, int i)
{
	char	*e;

	data->map.map[i] = ft_strdup(line);
	if (!data->map.map[i])
		exit_error("Error duplicating map line.", data);
	if ((e = ft_strchr(line, 'P')))
		set_player(data, i, line, e);
	if ((e = ft_strchr(line, 'E')))
		set_exit(data, i, line, e);
	if ((e = ft_strchr(line, 'C')))
		set_collectible(data, i, line);
}

void	clear_map_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->map.map)
	{
		while (i < data->map.size.y / TILE_SIZE)
			data->map.map[i++] = NULL;
		data->map.map = NULL;
	}
}

void	set_map(t_data	*data)
{
	int		i;
	int		fd;
	char	*line;

	data->collectibles.count = 0;
	fd = open(data->map.path, O_RDONLY);
	if (fd < 0)
		exit_error("Error opening map file.", data);
	i = 0;
	clear_map_data(data);
	while ((line = get_next_line(fd)) != NULL)
	{
		parse_map_line(data, line, i++);
		free(line);
	}
	data->map.map[i] = NULL;
	close(fd);

}

int	get_map_measurements(t_data *data)
{

	get_map_size(data);
	data->map.map = malloc(sizeof(char *) * (data->map.size.y + 1));
	if (!data->map.map)
		exit_error("Error allocating map.", data);
	set_map(data);
	data->map.size.y *= TILE_SIZE;
	return (1);
}
