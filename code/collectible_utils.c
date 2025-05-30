/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:36:46 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 14:43:13 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	remove_collectible(t_data *data, t_list *target, t_list *previous)
{
	if (previous)
	   previous->next = target->next;
	else
	   data->collectibles = target->next;
	free(target->content);
	free(target);
}

void	sort_collectibles(t_data *data)
{
	t_list	*current;
	t_list	*next;
	int		temp[2];

	current = data->collectibles;
	while (current && current->next)
	{
		next = current->next;
		while (next)
		{
			if (((int *)current->content)[0] > ((int *)next->content)[0] ||
				(((int *)current->content)[0] == ((int *)next->content)[0] &&
				((int *)current->content)[1] > ((int *)next->content)[1]))
			{
				temp[0] = ((int *)current->content)[0];
				temp[1] = ((int *)current->content)[1];
				((int *)current->content)[0] = ((int *)next->content)[0];
				((int *)current->content)[1] = ((int *)next->content)[1];
				((int *)next->content)[0] = temp[0];
				((int *)next->content)[1] = temp[1];
			}
			next = next->next;
		}
		current = current->next;
	}
}

int is_all_collectibles_collected(t_data *data)
{
	return (data->collected_collectibles == data->collectibles_total);
}

int	is_on_collectible(t_data *data)
{
	t_list	*previous;
	t_list	*current;

	previous = NULL;
	current = data->collectibles;

	while (current)
	{
		int *pos = (int *)current->content;
		if (pos[0] == data->player_pos[1] && pos[1] == data->player_pos[0])
		{
			data->map[pos[0]][pos[1]] = '0';
			data->collected_collectibles++;
			remove_collectible(data, current, previous);
			return (1);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}

void	move_to_collectible(t_data *data, t_list *collectible)
{
	int *pos = (int *)collectible->content;
	int *player_pos = data->player_pos;

	printf("Moving to collectible at (%d, %d)\n", pos[0], pos[1]);
	printf("Player position is (%d, %d)\n", player_pos[0], player_pos[1]);

	if (pos[1] < player_pos[1] && !is_next_tile_wall(data, -1, 0))
		data->x_offset += TILE_SIZE;
	else if (pos[1] > player_pos[1] && !is_next_tile_wall(data, 1, 0))
		data->x_offset -= TILE_SIZE;
	else if (pos[0] < player_pos[0] && !is_next_tile_wall(data, 0, -1))
		data->y_offset += TILE_SIZE;
	else if (pos[0] > player_pos[0] && !is_next_tile_wall(data, 0, 1))
		data->y_offset -= TILE_SIZE;
	else
	{
		printf("Cannot move to collectible at (%d, %d) due to walls.\n", pos[0], pos[1]);
		printf("Collectibles size: %d\n", ft_lstsize(data->collectibles));

	}

	if (is_on_collectible(data))
		printf("You collected %d collectibles!\n", data->collected_collectibles);
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

