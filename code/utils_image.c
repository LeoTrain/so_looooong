/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:37:50 by leberton          #+#    #+#             */
/*   Updated: 2025/07/31 11:23:16 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_bool	load_image(void *mlx, void **img, char *path, int *w, int *h)
{
	*img = mlx_xpm_file_to_image(mlx, path, w, h);
	if (!*img)
		return (false);
	return (true);
}
