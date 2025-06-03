/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_pathfinding_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 21:49:44 by leberton          #+#    #+#             */
/*   Updated: 2025/06/03 21:51:15 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_directions(t_position *directions)
{
	directions[0] = (t_position){-1, 0};
	directions[1] = (t_position){1, 0};
	directions[2] = (t_position){0, -1};
	directions[3] = (t_position){0, 1};
}

t_bool	is_valid(t_position position, int width, int height)
{
	return (position.x > 0 && position.x < width && position.y > 0 && position.y < height);
}

t_bool	is_same(t_position a, t_position b)
{
	return (a.x == b.x && a.y == b.y);
}

