// HEADER

#include "so_long.h"

static int	get_map_height(t_data *data)
{
	int		height;
	char	*line;

	height = 0;
	data->current_fd = open(data->map.path, O_RDONLY);
	if (data->current_fd < 0)
		exit_error("Error\nopening the map", data);
	while ((line = get_next_line(data->current_fd)) != NULL)
	{
		height++;
		free(line);
	}
	close(data->current_fd);
	data->current_fd = 0;
	return (height);
}

static int	get_map_width(t_data *data)
{
	int		current_width;
	int		max_width;
	char	*line;

	max_width = 0;
	current_width = 0;
	data->current_fd = open(data->map.path, O_RDONLY);
	if (data->current_fd < 0)
		exit_error("Error\nopening the map", data);
	while ((line = get_next_line(data->current_fd)) != NULL)
	{
		current_width = ft_strlen(line);
		if (current_width > max_width)
			max_width = current_width;
		free(line);
	}
	close(data->current_fd);
	data->current_fd = 0;
	return (max_width - 1);
}

void	get_map_size(t_data *data)
{
	data->map.tile_size.x = get_map_width(data);
	data->map.tile_size.y = get_map_height(data);
	data->map.size.x = data->map.tile_size.x * TILE_SIZE;
	data->map.size.y = data->map.tile_size.y * TILE_SIZE;
}
