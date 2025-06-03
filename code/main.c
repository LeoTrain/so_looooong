/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:33:03 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 17:10:53 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	p_position(t_position position, char *name)
{
	printf("Position for %s:\n	-x: %d\n	-y: %d\n", name, position.x, position.y);
}

int	ft_puterror(char *message, int error_code)
{
	printf("%s\n", message);
	return (error_code);
}

void	ft_debug(char *message)
{
	printf("Debug: %s\n", message);
}

void	free_all(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		free(data->mlx);
	}
	if (data->player_position.x >= 0 && data->player_position.y >= 0)
		free(data->player_pos);
	if (data->exit_position.x >= 0 && data->exit_position.y >= 0)
		free(data->exit_pos);
	if (data->map.map)
	{
		for (int i = 0; data->map.map[i]; i++)
			free(data->map.map[i]);
		free(data->map.map);
	}
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_puterror("Error: correct use case ./program_name <map.file>.", 1));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_puterror("Error: creating the mlx variable.", 2));
	data.win_size = 20 * TILE_SIZE;
	data.win = mlx_new_window(data.mlx, data.win_size, data.win_size, "Test1");
	if (!data.win)
		return (ft_puterror("Error: creating the window.", 2));
	data.assets.character.path = "assets/xpm/normal_amazed.xpm";
	data.assets.grass.path = "assets/empty_space.xpm";
	data.assets.wall.path = "assets/wall.xpm";
	data.assets.collectible.path = "assets/collectible.xpm";
	data.assets.exit.path = "assets/exit.xpm";
	load_image(data.mlx, (void **)&data.assets.character.img, data.assets.character.path, &data.map.tile_size.x, &data.map.tile_size.y);
	load_image(data.mlx, (void **)&data.assets.grass.img, data.assets.grass.path, &data.map.tile_size.x, &data.map.tile_size.y);
	load_image(data.mlx, (void **)&data.assets.wall.img, data.assets.wall.path, &data.map.tile_size.x, &data.map.tile_size.y);
	load_image(data.mlx, (void **)&data.assets.collectible.img, data.assets.collectible.path, &data.map.tile_size.x, &data.map.tile_size.y);
	data.map.path = argv[1];
	data.exit_position = (t_position){-1, -1};
	data.collectibles.count = 0;
	int collectible_coount = count_coullectible(&data);
	data.collectibles.collectibles = calloc(collectible_coount, sizeof(t_collectible));
	if (!data.collectibles.collectibles)
		return (ft_puterror("Error: allocating data.collectibles.collectibles in main.", 2));
	if (!get_map_measurements(&data))
		return (ft_puterror("Error: reading the map file.", 3));
	get_player_pos(&data);
	sort_collectibles(&data);
	data.path_length = 0;

	mlx_key_hook(data.win, (int (*)(int, void *))key_hook, &data);
	mlx_loop_hook(data.mlx, (int (*)(void *))loop_hook, &data);
	mlx_loop(data.mlx);
	free_all(&data);

	return (0);
}
