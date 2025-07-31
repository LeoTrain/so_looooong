/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:23:44 by leberton          #+#    #+#             */
/*   Updated: 2025/07/31 12:54:24 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_bool	is_x_bigger(t_position a, t_position b)
{
	return a.x > b.x;
}

t_position add_positions(t_position a, t_position b)
{
	t_position new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	return (new);
}
