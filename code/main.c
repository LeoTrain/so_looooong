/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:33:03 by leberton          #+#    #+#             */
/*   Updated: 2025/05/30 14:46:04 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_puterror(char *message, int error_code)
{
	printf("%s\n", message);
	return (error_code);
}

void	free_all(t_data *data)
{
	if (data->character_img)
		mlx_destroy_image(data->mlx, data->character_img);
	if (data->grass_img)
		mlx_destroy_image(data->mlx, data->grass_img);
	if (data->wall_img)
		mlx_destroy_image(data->mlx, data->wall_img);
	if (data->collectible_img)
		mlx_destroy_image(data->mlx, data->collectible_img);
	if (data->mapexit_img)
		mlx_destroy_image(data->mlx, data->mapexit_img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->player_pos)
		free(data->player_pos);
	if (data->exit_pos)
		free(data->exit_pos);
	if (data->map)
	{
		for (int i = 0; data->map[i]; i++)
			free(data->map[i]);
		free(data->map);
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
	data.character_xpm_path = "assets/xpm/normal_amazed.xpm";
	data.grass_xpm_path = "assets/empty_space.xpm";
	data.wall_xpm_path = "assets/wall.xpm";
	data.collectible_xpm_path = "assets/collectible.xpm";
	data.mapexit_xpm_path = "assets/exit.xpm";
	load_image(data.mlx, (void **)&data.character_img, data.character_xpm_path, &data.tile_size, &data.tile_size);
	load_image(data.mlx, (void **)&data.grass_img, data.grass_xpm_path, &data.tile_size, &data.tile_size);
	load_image(data.mlx, (void **)&data.wall_img, data.wall_xpm_path, &data.tile_size, &data.tile_size);
	load_image(data.mlx, (void **)&data.collectible_img, data.collectible_xpm_path, &data.tile_size, &data.tile_size);
	data.map = NULL;
	data.map_path = argv[1];
	data.x = 0;
	data.y = 0;
	data.exit_pos = NULL;
	data.collectibles = NULL;
	data.collected_collectibles = 0;
	data.collectibles_total = 0;
	if (!get_map_measurements(&data))
		return (ft_puterror("Error: reading the map file.", 3));
	get_player_pos(&data);
	ft_pcoll(data.collectibles);
	sort_collectibles(&data);
	ft_pcoll(data.collectibles);
	
	mlx_key_hook(data.win, (int (*)(int, void *))key_hook, &data);
	mlx_loop_hook(data.mlx, (int (*)(void *))loop_hook, &data);
	mlx_loop(data.mlx);
	free_all(&data);

	return (0);
}
