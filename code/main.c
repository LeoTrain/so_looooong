/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:33:03 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 21:05:51 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		exit_error("Error\ncorrect use case ./program_name <map.file>.", &data);
	init_game(&data, argv[1]);
	mlx_key_hook(data.win, (int (*)(int, void *))key_hook, &data);
	mlx_loop_hook(data.mlx, (int (*)(void *))loop_hook, &data);
	mlx_loop(data.mlx);
	free_all(&data);
	return (0);
}
