/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:39:23 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/21 21:02:46 by fbosch           ###   ########.fr       */
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
	if (data->key.right_clicked)
	{
		if (data->key.first_right_click == true)
		{
			data->key.first_right_click = false;
			last_x = x;
			last_y = y;
		}
		data->map.translate[X] += x - last_x;
		data->map.translate[Y] += y - last_y;
		last_x = x;
		last_y = y;
		init_visualization(data, &data->map);
	}
	if (data->key.left_clicked)
	{
		if (data->key.first_left_click == true)
		{
			data->key.first_left_click = false;
			last_x = x;
			last_y = y;
		}
		data->map.rotate[X] -= y - last_y;
		data->map.rotate[Y] -= x - last_x;
		last_x = x;
		last_y = y;
		init_visualization(data, &data->map);
	}
	return (0);
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
	//if (key == X_KEY || key == Y_KEY || key == Z_KEY)
		//rotate_object(param, key);
	return (0);
}

int	mouse_down(int button, int x, int y, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (button == SCROLL_DOWN)
		zoom_screen(param, 1.2);
	else if (button == SCROLL_UP)
		zoom_screen(param, 0.8);
	else if (button == RIGHT_CLICK)
		data->key.right_clicked = true;
	else if (button == LEFT_CLICK)
		data->key.left_clicked = true;
	init_visualization(data, &data->map);
	return (0);
}

int	mouse_up(int button, int x, int y, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (button == RIGHT_CLICK)
	{
		data->key.first_right_click = true;
		data->key.right_clicked = false;
	}
	else if (button == LEFT_CLICK)
	{
		data->key.first_left_click = true;
		data->key.left_clicked = false;
	}
	return (0);
}
