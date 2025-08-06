/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:03:24 by leberton          #+#    #+#             */
/*   Updated: 2025/08/06 21:05:11 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	set_player(t_data *data, int y, char *line, char *e)
{
	t_position	player_pos;

	if (data->is_player_set == 1 || is_another_on_line('P', line))
	{
		free_current_map(data, y);
		exit_error("Error\ntoo many player starting positions.", data);
	}
	player_pos.y = y;
	player_pos.x = (int)(e - line);
	set_player_pos(data, player_pos);
	data->offset.x = (data->win_width / 2) - data->map.player_position.x;
	data->offset.y = (data->win_height / 2) - data->map.player_position.y;
	data->is_player_set = 1;
}

void	set_exit(t_data *data, int y, char *line, char *e)
{
	t_position	exit_pos;

	if (data->found_exit == 1 || is_another_on_line('E', line))
	{
		free_current_map(data, y);
		exit_error("Error\ntoo many exit positions.", data);
	}
	data->found_exit = 1;
	exit_pos.x = (int)(e - line);
	exit_pos.y = y;
	data->map.exit_position = exit_pos;
}

void	set_collectible(t_data *data, int y, char *line)
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
