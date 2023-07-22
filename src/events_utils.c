/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:46:50 by fbosch            #+#    #+#             */
/*   Updated: 2023/07/22 03:54:59 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	change_theme(t_mlx *data, int key)
{
	if (key == ONE_KEY)
	{
		data->map.theme[BG_C] = BLACK;
		data->map.theme[OBJ1_C] = ORANGE;
		data->map.theme[OBJ2_C] = WHITE;
	}
	else if (key == TWO_KEY)
	{
		data->map.theme[BG_C] = BLACK;
		data->map.theme[OBJ1_C] = PINK;
		data->map.theme[OBJ2_C] = GREEN;
	}
	else if (key == THREE_KEY)
	{
		data->map.theme[BG_C] = WHITE;
		data->map.theme[OBJ1_C] = BLUE_DARK;
		data->map.theme[OBJ2_C] = BROWN;
	}
	map_colors(&data->map);
	init_visualization(data);
}

void	rotate_object(t_mlx *data, int key)
{
	if (key == X_KEY)
		data->map.rotate[X] += ROTATION;
	else if (key == Y_KEY)
		data->map.rotate[Y] += ROTATION;
	else if (key == Z_KEY)
		data->map.rotate[Z] += ROTATION;
	init_visualization(data);
}

void	move_map(t_mlx *data, int key)
{
	if (key == A_KEY)
		data->map.translate[X] -= TRANSL;
	if (key == S_KEY)
		data->map.translate[Y] += TRANSL;
	if (key == D_KEY)
		data->map.translate[X] += TRANSL;
	if (key == W_KEY)
		data->map.translate[Y] -= TRANSL;
	init_visualization(data);
}

void	change_height(t_mlx *data, int key)
{
	float	height;

	if (key == M_KEY)
		height = HEIGHT_UP;
	else
		height = HEIGHT_DOWN;
	data->map.z_resize *= height;
	init_visualization(data);
}

void	zoom_screen(t_mlx *data, int button)
{
	float	zoom;

	if (button == SCROLL_DOWN)
		zoom = ZOOM_IN;
	else
		zoom = ZOOM_OUT;
	data->map.zoom *= zoom;
	init_visualization(data);
}

int	close_program(t_mlx *data, int exit_code)
{
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy(data->mlx);
	free(data->map.terrain);
	exit(exit_code);
}

void	change_mode(t_mlx *data)
{
	data->map.mode = ((data->map.mode + 1) % 2) + 30;
	init_visualization(data);
}
