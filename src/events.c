/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:39:23 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/14 19:21:13 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

int	mouse_move(int x, int y, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (data->key.mid_clicked)
		ft_printf("%i, %i\n", x, y);
	return (0);
}

int	key_down(int keycode, void *param)
{
	if (keycode == ESC_KEY)
		close_program(param, EXIT_SUCCESS);
	if (keycode == PLUS_KEY)
		zoom_screen(param, 1.2);
	if (keycode == MINUS_KEY)
		zoom_screen(param, 0.8);
	if (keycode == O_KEY)
		change_height(param, -1);
	if (keycode == P_KEY)
		change_height(param, 1);
	return (0);
}

int	mouse_down(int button, int x, int y, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (button == SCROLL_DOWN)
		zoom_screen(param, 1.2);
	if (button == SCROLL_UP)
		zoom_screen(param, 0.8);
	if (button == MID_CLICK)
		data->key.mid_clicked = 1;
	return (0);
}

int	mouse_up(int button, int x, int y, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (button == MID_CLICK)
		data->key.mid_clicked = 0;
	return (0);
}

void	iterate_terrain(t_map *map, int delta)
{
	int		x;
	int		y;
	float	mult;

	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
		{
			if (map->terrain[y][x].z)
				map->terrain[y][x].z += delta;
			x++;
		}
		y++;
	}
}

void	change_height(void *param, int delta)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	iterate_terrain(&data->map, delta);
	init_visualization(data, &data->map);
}

void	zoom_screen(void *param, float zoom)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	data->map.zoom *= zoom;
	init_visualization(data, &data->map);
}

int	close_program(void *param, int exit_code)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy(data->mlx);
	free_terrain(&data->map, data->map.y_size - 1);
	exit(exit_code);
}
