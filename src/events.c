/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:39:23 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/20 17:37:47 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	mouse_move(int x, int y, void *param)
{
	static int	last_x = 0;
	static int	last_y = 0;
	t_mlx	*data;

	data = (t_mlx *)param;
	if (data->key.mid_clicked)
	{
		if (data->key.first_mid_click == 1)
		{
			data->key.first_mid_click = 0;
			last_x = x;
			last_y = y;
		}
		data->map.translate[X] += x - last_x;
		data->map.translate[Y] += y - last_y;
		last_x = x;
		last_y = y;
		//init_visualization(data, &data->map);
	}
	return (0);
}

void	rotate_x(void *param)
{
	t_mlx	*data;

	ft_printf("a");
	data = (t_mlx *)param;
	data->map.rotate[X] += 3;
	init_visualization(data, &data->map);
}

int	key_down(int key, void *param)
{
	if (key == ESC_KEY)
		close_program(param, EXIT_SUCCESS);
	else if (key == PLUS_KEY)
		zoom_screen(param, ZOOM_IN);
	else if (key == MINUS_KEY)
		zoom_screen(param, ZOOM_OUT);
	else if (key == A_KEY || key == S_KEY || key == D_KEY || key == W_KEY)
		move_map(param, key);
	if (key == O_KEY)
		zoom_screen(param, 0.8);
	if (key == P_KEY)
		zoom_screen(param, 1.2);
	if (key == T_KEY)
		rotate_x(param);
	return (0);
}

void	move_map(void *param, int key)
{
	t_mlx *data;

	data = (t_mlx *)param;
	if (key == A_KEY)
		data->map.translate[X] -= TRANSL;
	if (key == S_KEY)
		data->map.translate[Y] += TRANSL;
	if (key == D_KEY)
		data->map.translate[X] += TRANSL;
	if (key == W_KEY)
		data->map.translate[Y] -= TRANSL;
	init_visualization(data, &data->map);
}

int	mouse_down(int button, int x, int y, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (button == SCROLL_DOWN)
		zoom_screen(param, 1.2);
	else if (button == SCROLL_UP)
		zoom_screen(param, 0.8);
	else if (button == MID_CLICK)
		data->key.mid_clicked = 1;
	init_visualization(data, &data->map);
	return (0);
}

int	mouse_up(int button, int x, int y, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (button == MID_CLICK)
	{
		data->key.first_mid_click = 1;
		data->key.mid_clicked = 0;
	}
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
			//if (map->terrain[y][x].z != map->floor)
			//	map->terrain[y][x].z += delta;
			x++;
		}
		y++;
	}
}

void	change_height(void *param, int delta)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	//iterate_terrain(&data->map, delta);
	//init_visualization(data, &data->map);
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
	free(data->map.terrain);
	exit(exit_code);
}
