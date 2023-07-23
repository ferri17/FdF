/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:39:23 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/23 12:07:46 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	mouse_move(int x, int y, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (data->key.right_clicked)
		translate_map_mouse(data, x, y);
	if (data->key.left_clicked)
		rotate_map_mouse(data, x, y);
	return (0);
}

int	key_down(int key, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (key == ESC_KEY)
		close_program(data, EXIT_SUCCESS);
	else if (key == A_KEY || key == S_KEY || key == D_KEY || key == W_KEY)
		move_map(data, key);
	else if (key == N_KEY || key == M_KEY)
		change_height(data, key);
	else if (key == G_KEY)
		change_mode(data);
	else if (key == ONE_KEY || key == TWO_KEY || key == THREE_KEY)
		change_theme(data, key);
	else if (key == X_KEY || key == Y_KEY || key == Z_KEY)
		lock_rotation_axis(data, key);
	else if (key == I_KEY || key == P_KEY)
		rotate_object(data, key);
	else if (key == O_KEY)
		snap_orto_projection(data);
	return (0);
}

int	key_up(int key, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (key == X_KEY)
		data->key.axis_locked[Y] = false;
	else if (key == Y_KEY)
		data->key.axis_locked[X] = false;
	else if (key == Z_KEY || key == O_KEY)
	{
		data->key.axis_locked[X] = false;
		data->key.axis_locked[Y] = false;
		data->key.axis_locked[Z] = true;
	}
	init_visualization(data);
	return (0);
}

int	mouse_down(int button, int x, int y, void *param)
{
	t_mlx	*data;

	data = (t_mlx *)param;
	if (button == SCROLL_DOWN)
		zoom_screen(data, button);
	else if (button == SCROLL_UP)
		zoom_screen(data, button);
	else if (button == RIGHT_CLICK)
		data->key.right_clicked = true;
	else if (button == LEFT_CLICK)
		data->key.left_clicked = true;
	init_visualization(data);
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
