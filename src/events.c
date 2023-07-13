/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:39:23 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/13 19:18:15 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"

int	mouse_move(int x, int y, void *param)
{
	t_mlx	*data = (t_mlx *)param;

	if (data->key.mid_clicked)
		ft_printf("%i, %i\n", x, y);
	return (0);
}

int	key_down(int keycode, void *param)
{
	if (keycode == ESC_KEY)
		close_program(param, EXIT_SUCCESS);
	if (keycode == PLUS_KEY)
		zoom_in(param);
	if (keycode == MINUS_KEY)
		zoom_out(param);
 	if (keycode == O_KEY)
		height_down(param);
	if (keycode == P_KEY)
		height_up(param);
	return (0);
}

int	mouse_down(int button, int x,int y, void *param)
{
	t_mlx	*data = (t_mlx *)param;
	
	if (button == SCROLL_DOWN)
		zoom_in(param);
	if (button == SCROLL_UP)
		zoom_out(param);
	if (button == MID_CLICK)
	{
		data->key.mid_clicked = 1;
	}
	return (0);
}

int	mouse_up(int button, int x,int y, void *param)
{
	t_mlx	*data = (t_mlx *)param;
	
	if (button == MID_CLICK)
	{
		data->key.mid_clicked = 0;
	}
	return (0);
}

void	iterate_terrain(t_map *map, int	delta)
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

void	height_up(void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	iterate_terrain(&data->map, 1);
	init_visualization(data, &data->map);
}

void	height_down(void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	iterate_terrain(&data->map, -1);
	init_visualization(data, &data->map);
}

void	zoom_in(void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	data->map.zoom *= 1.2;
	init_visualization(data, &data->map);
}

void	zoom_out(void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	data->map.zoom /= 1.2;
	init_visualization(data, &data->map);
}

int	close_program(void *param, int exit_code)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy(data->mlx);
	exit(exit_code);
}
