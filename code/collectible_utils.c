/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:36:46 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 17:14:21 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "so_long.h"
#include <fcntl.h>

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

int	get_total_collected(t_data *data)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < data->collectibles.count)
	{
		if (data->collectibles.collectibles[i].collected)
			count++;
		i++;
	}
	return (count);
}

void add_collectible(t_data *data, t_position pos)
{
	t_collectible new_collectible;
	new_collectible.position = pos;
	new_collectible.collected = false;
	data->collectibles.collectibles[data->collectibles.count] = new_collectible;
	data->collectibles.count++;
}

int ft_pcoll(t_list *data)
{
	t_list *curr = data;
	int i = 1;
	while (curr)
	{
		printf("Collectible %d: (%d, %d)\n", i,
			((int *)curr->content)[0],
			((int *)curr->content)[1]);
		curr = curr->next;
		i++;
	}
	printf("\n\n\n");
	return (0);
}

void	sort_collectibles(t_data *data)
{
	t_collectible	current;
	t_collectible	next;
	t_collectible	temp;

	current = data->collectibles.collectibles[0];
	while (1)
	{
		int swapped = 0;
		for (int i = 0; i < data->collectibles.count - 1; i++)
		{
			current = data->collectibles.collectibles[i];
			next = data->collectibles.collectibles[i + 1];
			if (current.position.y > next.position.y ||
				(current.position.y == next.position.y && current.position.x > next.position.x))
			{
				temp = current;
				data->collectibles.collectibles[i] = next;
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

	i = 0;
	if (data->map.map[data->player_position.y][data->player_position.x] == 'C')
	{
		while (i < data->collectibles.count)
		{
			if (data->collectibles.collectibles[i].position.x == data->player_position.x &&
				data->collectibles.collectibles[i].position.y == data->player_position.y)
			{
				data->map.map[data->player_position.y][data->player_position.x] = '0';
				data->collectibles.collectibles[i].collected = true;
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int	is_wall_at(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map.size.y / TILE_SIZE ||
		y < 0 || y >= data->map.size.x / TILE_SIZE)
		return (1);
	if (data->map.map[x][y] == '1')
		return (1);
	return (0);
}

static t_position get_next_step(t_data *data, t_position target)
{
    int real_y = data->player_position.y - (data->offset.y / TILE_SIZE);
    int real_x = data->player_position.x - (data->offset.x / TILE_SIZE);
    int cols = data->map.size.x / TILE_SIZE;
    int rows = data->map.size.y / TILE_SIZE;
    t_bool visited[cols][rows];
    t_position parent[rows][cols];
    memset(visited, 0, sizeof(visited));
    t_queue *q = queue_new();
    t_position start = { real_x, real_y };

    visited[start.y][start.x] = true;
    queue_push(q, start);
    const t_position dirs[4] = {{-1,0},{1,0},{0,-1},{0,1}};
    while (!queue_empty(q))
    {
        t_position cur = queue_pop(q);
        if (cur.x == target.x && cur.y == target.y)
            break;
        for (int i = 0; i < 4; ++i)
        {
            t_position nxt = { cur.x + dirs[i].x, cur.y + dirs[i].y };
            if (nxt.y < 0 || nxt.y >= rows || nxt.x < 0 || nxt.x >= cols)
                continue;
            if (visited[nxt.y][nxt.x] || is_wall_at(data, nxt.x, nxt.y))
                continue;
            visited[nxt.y][nxt.x] = true;
            parent[nxt.y][nxt.x] = cur;
            queue_push(q, nxt);
        }
    }
    t_position step = target;
    if (!visited[target.y][target.x])
    {
        queue_free(q);
        return (t_position){0, 0};
    }
    while (parent[step.y][step.x].x != start.x || parent[step.y][step.x].y != start.y)
        step = parent[step.y][step.x];
    queue_free(q);
    return (t_position){ step.x - start.x, step.y - start.y };
}

void move_to_collectible(t_data *data, t_collectible *collectible)
{
    t_position pos = collectible->position;
    t_position delta = get_next_step(data, pos);

    if (delta.x != 0 || delta.y != 0)
    {
        if (delta.y == -1)
            data->offset.y += TILE_SIZE;
        else if (delta.y == 1)
            data->offset.y -= TILE_SIZE;
        if (delta.x == -1)
            data->offset.x += TILE_SIZE;
        else if (delta.x == 1)
            data->offset.x -= TILE_SIZE;
    }
    else
        printf("Blocked: no path to collectible (%d, %d)\n", pos.x, pos.y);
}




