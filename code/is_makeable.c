/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_makeable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:06:50 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 18:38:00 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	is_makeable(t_data *data, int x, int y)
{
	if (data->map.map[y][x] == '1' || data->map.map[y][x] == 'V')
		return;
	if (data->map.map[y][x] == 'C')
		data->found_collectible++;
	if (data->map.map[y][x] == 'E')
		data->found_exit = 1;
	data->map.map[y][x] = 'V';
	is_makeable(data, x + 1, y);
	is_makeable(data, x - 1, y);
	is_makeable(data, x, y + 1);
	is_makeable(data, x, y - 1);
}
