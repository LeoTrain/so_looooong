/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:37:50 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 14:38:05 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_image(void *mlx, void **img, char *path, int *w, int *h)
{
	*img = mlx_xpm_file_to_image(mlx, path, w, h);
}
