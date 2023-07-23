/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:45:17 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/23 12:08:42 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	translate_map_mouse(t_mlx *data, int x, int y)
{
	static int	last_x = 0;
	static int	last_y = 0;

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
	init_visualization(data);
}

void	rotate_map_mouse(t_mlx *data, int x, int y)
{
	static int	last_x = 0;
	static int	last_y = 0;

	if (data->key.first_left_click == true)
	{
		data->key.first_left_click = false;
		last_x = x;
		last_y = y;
	}
	if (!data->key.axis_locked[X])
		data->map.rotate[X] += y - last_y;
	if (!data->key.axis_locked[Y])
		data->map.rotate[Y] -= x - last_x;
	if (!data->key.axis_locked[Z])
		data->map.rotate[Z] -= x - last_x;
	last_x = x;
	last_y = y;
	init_visualization(data);
}

void	snap_orto_projection(t_mlx *data)
{
	if (abs(data->map.rotate[X]) % 90 < 10
		|| abs(data->map.rotate[X]) % 90 > 80)
	{
		if (abs(data->map.rotate[X]) % 90 < 10)
			data->map.rotate[X] -= data->map.rotate[X] % 90;
		else if (abs(data->map.rotate[X]) % 90 > 80)
			data->map.rotate[X] += 90 - (data->map.rotate[X] % 90);
		if (data->map.rotate[Y] % 90 <= 45)
			data->map.rotate[Y] -= data->map.rotate[Y] % 90;
		else if (data->map.rotate[Y] % 90 > 45)
			data->map.rotate[Y] += 90 - (data->map.rotate[Y] % 90);
		if (data->map.rotate[Z] % 90 <= 45)
			data->map.rotate[Z] -= data->map.rotate[Z] % 90;
		else if (data->map.rotate[Z] % 90 > 45)
			data->map.rotate[Z] += 90 - (data->map.rotate[Z] % 90);
		data->key.axis_locked[X] = true;
		data->key.axis_locked[Y] = true;
		data->key.axis_locked[Z] = true;
	}
}

void	lock_rotation_axis(t_mlx *data, int key)
{
	if (key == X_KEY)
	{
		data->key.axis_locked[Y] = true;
		data->key.axis_locked[Z] = true;
	}
	else if (key == Y_KEY)
	{
		data->key.axis_locked[X] = true;
		data->key.axis_locked[Z] = true;
	}
	else if (key == Z_KEY)
	{
		data->key.axis_locked[X] = true;
		data->key.axis_locked[Y] = true;
		data->key.axis_locked[Z] = false;
	}
	init_visualization(data);
}

void	change_theme(t_mlx *data, int key)
{
	if (key == ONE_KEY)
	{
		data->map.theme[BG_C] = GRAY_DARK;
		data->map.theme[OBJ1_C] = ORANGE;
		data->map.theme[OBJ2_C] = WHITE;
		data->map.theme[MENU] = BLACK;
	}
	else if (key == TWO_KEY)
	{
		data->map.theme[BG_C] = GRAY_DARK;
		data->map.theme[OBJ1_C] = PINK;
		data->map.theme[OBJ2_C] = GREEN;
		data->map.theme[MENU] = BLACK;
	}
	else if (key == THREE_KEY)
	{
		data->map.theme[BG_C] = WHITE;
		data->map.theme[OBJ1_C] = BLACK;
		data->map.theme[OBJ2_C] = BLUE_DARK;
		data->map.theme[MENU] = BLACK;
	}
	map_colors(&data->map);
	init_visualization(data);
}
