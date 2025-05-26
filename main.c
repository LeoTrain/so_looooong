/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:33:03 by leberton          #+#    #+#             */
/*   Updated: 2025/05/26 16:52:50 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "so_long.h"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
}			t_data;

void	draw_red_cube(t_data *data)
{
	int	x;
	int	y;

	mlx_clear_window(data->mlx, data->win);
	y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
		{
			mlx_pixel_put(data->mlx, data->win, x + data->x, y + data->y, 0xFF0000);
			x++;
		}
		y++;
	}
}

int	move_cube(t_data *data)
{
	static int	direction;

	if (!direction)
		direction = 1;
	draw_red_cube(data);
	data->x += direction;
	if (data->x > 400 || data->x < 0)
		direction = -direction;
	draw_red_cube(data);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 119)
		data->y -= 10;
	else if (keycode == 115)
		data->y += 10;
	else if (keycode == 100)
		data->x += 10;
	else if (keycode == 97)
		data->x -= 10;
	return (0);
}

int	loop_hook(t_data *data)
{
	draw_red_cube(data);
	return (0);
}

int main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 500, 500, "Test1");
	if (!data.win)
		return (1);
	data.x = 200;
	data.y = 200;
	
	mlx_key_hook(data.win, (int (*)(int, void *))key_hook, &data);
	mlx_loop_hook(data.mlx, (int (*)(void *))loop_hook, &data);
	mlx_loop(data.mlx);

	return (0);
}
