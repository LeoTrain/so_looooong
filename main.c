/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:33:03 by leberton          #+#    #+#             */
/*   Updated: 2025/05/26 16:59:31 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		x_offset;
	int		y_offset;
	char	*character_xpm_path;
	void	*character_img;
	int		character_height;
	int		character_width;
	char	*grass_xpm_path;
	void	*grass_img;
	int		grass_height;
	int		grass_width;
	char	*wall_xpm_path;
	void	*wall_img;
	int		wall_height;
	int		wall_width;
	char	*collectible_xpm_path;
	void	*collectible_img;
	int		collectible_height;
	int		collectible_width;
	char	*mapexit_xpm_path;
	void	*mapexit_img;
	int		mapexit_height;
	int		mapexit_width;
	char	*map_path;
	int		map_width;
	int		map_height;
}			t_data;

void	get_map_measurements(t_data *data)
{
	int		fd;
	char	*line;
	char	*e;

	fd = open(data->map_path, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		data->map_width = strlen(line) + 1;
		data->map_height++;
		if ((e = strchr(line, 'P')))
		{
			data->y = data->map_height - 1;
			data->x = (int)(e - line);
		}
		free(line);
	}
	free(line);
	close(fd);
}

long	get_time_in_ms(void)
{
	struct	timeval	timev;
	gettimeofday(&timev, NULL);
	return (timev.tv_sec * 1000 + timev.tv_usec / 1000);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 119)
		data->y_offset -= 1;
	else if (keycode == 115)
		data->y_offset += 1;
	else if (keycode == 100)
		data->x_offset += 1;
	else if (keycode == 97)
		data->x_offset -= 1;
	return (0);
}

void	draw(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	for (int i = 0; i <= data->map_width; i++)
		for (int j = 0; j <= data->map_height; j++)
			mlx_put_image_to_window(data->mlx, data->win, data->grass_img, (data->grass_width*i)-data->x_offset, (data->grass_height*j)-data->y_offset);
	mlx_put_image_to_window(data->mlx, data->win, data->character_img, 250-8, 250-8);
}

int	loop_hook(t_data *data)
{
	static long	last_time;
	long		current_time;

	if (last_time == 0)
		last_time = get_time_in_ms();
	current_time = get_time_in_ms();

	if (current_time - last_time >= 16)
	{
		last_time = current_time;
		draw(data);
	}
	return (0);
}

int	ft_puterror(char *message, int error_code)
{
	printf("%s\n", message);
	return (error_code);
}


int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_puterror("Error: correct use case ./program_name <map.file>.", 1));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_puterror("Error: creating the mlx variable.", 2));
	data.win = mlx_new_window(data.mlx, 500, 500, "Test1");
	if (!data.win)
		return (ft_puterror("Error: creating the window.", 2));
	data.x = 200;
	data.y = 200;
	data.character_xpm_path = "assets/xpm/normal_amazed.xpm";
	data.grass_xpm_path = "assets/xpm/grass_block.xpm";
	data.wall_xpm_path = "assets/xpm/dirt.xpm";
	data.collectible_xpm_path = "assets/xpm/grass.xpm";
	data.mapexit_xpm_path = "assets/xpm/grass.xpm";
	data.character_img = mlx_xpm_file_to_image(data.mlx, data.character_xpm_path, &data.character_width, &data.character_height);
	data.grass_img = mlx_xpm_file_to_image(data.mlx, data.grass_xpm_path, &data.grass_width, &data.grass_height);
	data.wall_img = mlx_xpm_file_to_image(data.mlx, data.wall_xpm_path, &data.wall_width, &data.wall_height);
	data.collectible_img = mlx_xpm_file_to_image(data.mlx, data.collectible_xpm_path, &data.collectible_width, &data.collectible_height);
	data.mapexit_img = mlx_xpm_file_to_image(data.mlx, data.mapexit_xpm_path, &data.mapexit_width, &data.mapexit_height);
	data.map_path = argv[1];
	get_map_measurements(&data);
	
	mlx_key_hook(data.win, (int (*)(int, void *))key_hook, &data);
	mlx_loop_hook(data.mlx, (int (*)(void *))loop_hook, &data);
	mlx_loop(data.mlx);

	return (0);
}
