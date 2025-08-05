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
	int		len;
	int		max_len;
	char	*line;

	max_len = 0;
	data->current_fd = open(data->map.path, O_RDONLY);
	if (data->current_fd < 0)
		exit_error("Error\nopening the map", data);
	data->map.size.y = 0;
	while ((line = get_next_line(data->current_fd)) != NULL)
	{
		len = ft_strlen(line);
		if (len > max_len)
			max_len = len;
		data->map.size.y++;
		free(line);
	}
	data->map.size.x = max_len * TILE_SIZE;
	close(data->current_fd);
	data->current_fd = 0;
}

static void	free_current_map(t_data *data, int i)
{
	while (--i >= 0)
	{
		free(data->map.map_is_makeable[i]);
		free(data->map.map[i]);
	}
	free(data->map.map_is_makeable);
	data->map.map_is_makeable = NULL;
	free(data->map.map);
	data->map.map = NULL;
}

static int	is_another_on_line(char c, char *line)
{
	int		found;
	char	*p_line;

	found = 0;
	p_line = line;
	while (*p_line)
	{
		if (*p_line == c)
			found++;
		p_line++;
	}
	return (found != 1);
}

static	void	set_player(t_data *data, int y, char *line, char *e)
{
	t_position	player_pos;

	if (data->is_player_set || is_another_on_line('P', line))
	{
		free_current_map(data, y);
		exit_error("Error\ntoo many player starting positions.", data);
	}
	player_pos.y = y * TILE_SIZE + TILE_SIZE;
	player_pos.x = ((int)(e - line) * TILE_SIZE) + TILE_SIZE;
	set_player_pos(data, player_pos);
	data->offset.x = (data->win_size / 2) - player_pos.x;
	data->offset.y = (data->win_size / 2) - player_pos.y;
}

static void	set_exit(t_data *data, int y, char *line, char *e)
{
	t_position	exit_pos;

	if (data->found_exit || is_another_on_line('E', line))
	{
		free_current_map(data, y);
		exit_error("Error\ntoo many exit positions.", data);
	}
	data->found_exit = 1;
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
	data->map.map_is_makeable[i] = ft_strdup(line);
	if (!data->map.map[i])
		exit_error("Error\nduplicating map line.", data);
	if (!data->map.map_is_makeable[i])
		exit_error("Error\nduplicating map is makeable line.", data);
	if ((e = ft_strchr(line, 'P')))
		set_player(data, i, line, e);
	if ((e = ft_strchr(line, 'E')))
		set_exit(data, i, line, e);
	if ((e = ft_strchr(line, 'C')))
		set_collectible(data, i, line);
}

static void	set_map(t_data	*data)
{
	int		i;
	char	*line;

	data->collectibles.count = 0;
	data->current_fd = open(data->map.path, O_RDONLY);
	if (data->current_fd < 0)
		exit_error("Error\nopening map file.", data);
	i = 0;
	while ((line = get_next_line(data->current_fd)) != NULL)
	{
		parse_map_line(data, line, i++);
		free(line);
	}
	data->map.map[i] = NULL;
	data->map.map_is_makeable[i] = NULL;
	close(data->current_fd);
	data->current_fd = 0;

}

static int	is_rectangular(t_data *data)
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
	return (1);
}
static int	is_surrounded_by_wall(t_data *data)
{
	int	x;
	int	y;

	is_rectangular(data);
	x = 0;
	y = 0;
	if (data->map.map)
	{
		while (y < data->map.size.y)
		{
			if (data->map.map[y][0] != '1' || data->map.map[y][data->map.size.x] != '1')
			{
				ft_printf("Wall at y == %d = %c or %c\n", y, data->map.map[y][0], data->map.map[y][max_x]);
				exit_error("Error\nmap is not surrounded by walls.\n", data);
			}
			y++;
		}
		while (x < data->map.size.x)
		{
			if (data->map.map[0][x] != '1' || data->map.map[data->map.size.y][x] != '1')
				exit_error("Error\nmap is not surrounded by walls.\n", data);
			x++;
		}
	}
	return (1);
}

int	get_map_measurements(t_data *data)
{
	get_map_size(data);
	printf("%d\n", data->map.size.y);
	data->map.map = malloc(sizeof(char *) * (data->map.size.y + 1));
	data->map.map_is_makeable = malloc(sizeof(char *) * (data->map.size.y + 1));
	if (!data->map.map)
		exit_error("Error\nallocating map.", data);
	if (!data->map.map_is_makeable)
		exit_error("Error\nallocating map for is_makeable.", data);
	set_map(data);
	data->map.size.y *= TILE_SIZE;
	is_surrounded_by_wall(data);
	return (1);
}
