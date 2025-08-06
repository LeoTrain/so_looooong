//HEADER

#include "so_long.h"

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

void	parse_map(t_data *data)
{
	int		i;
	char	*line;

	i = 0;
	data->current_fd = open(data->map.path, O_RDONLY);
	if (data->current_fd < 0)
		exit_error("Error\nopening map file.", data);
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

void	allocate_for_map(t_data *data)
{
	data->map.map = malloc(sizeof(char *) * (data->map.size.y + 1));
	data->map.map_is_makeable = malloc(sizeof(char *) * (data->map.size.y + 1));
	if (!data->map.map)
		exit_error("Error\nallocating for map.", data);
	if (!data->map.map_is_makeable)
		exit_error("Error\nallocating for is_makeable.", data);
}

