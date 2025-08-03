/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:33:03 by leberton          #+#    #+#             */
/*   Updated: 2025/08/03 19:08:31 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_error_code(int error_code, t_data *data)
{
	if (error_code == 0)
		return ;
	if (error_code == 1)
		ft_puterror("Error\nthe map is not makeable.", data);
	else if (error_code == 1002)
		ft_puterror("Error\nnot able to initialize the map.", data);
	else if (error_code == 1003)
		ft_puterror("Error\nnot able to initialize the assets.", data);
	if (error_code == 1004)
		ft_puterror("Error\nnot able to initialize the data.", data);
}

int main(int argc, char **argv)
{
	t_data	data;
	int		error_code;

	if (argc != 2)
		ft_puterror("Error\ncorrect use case ./program_name <map.file>.", &data);
	error_code = init_game(&data, argv[1]);
	check_error_code(error_code, &data);
	mlx_key_hook(data.win, (int (*)(int, void *))key_hook, &data);
	mlx_loop_hook(data.mlx, (int (*)(void *))loop_hook, &data);
	mlx_loop(data.mlx);
	free_all(&data);
	return (0);
}
